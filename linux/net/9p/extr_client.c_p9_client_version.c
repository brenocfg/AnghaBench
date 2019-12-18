#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct p9_req_t {int /*<<< orphan*/  rc; } ;
struct p9_client {int msize; int proto_version; } ;

/* Variables and functions */
 int EINVAL ; 
 int EREMOTEIO ; 
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_TVERSION ; 
 int PTR_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,...) ; 
#define  p9_proto_2000L 130 
#define  p9_proto_2000u 129 
#define  p9_proto_legacy 128 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 
 int p9pdu_readf (int /*<<< orphan*/ *,int,char*,int*,char**) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p9_client_version(struct p9_client *c)
{
	int err = 0;
	struct p9_req_t *req;
	char *version = NULL;
	int msize;

	p9_debug(P9_DEBUG_9P, ">>> TVERSION msize %d protocol %d\n",
		 c->msize, c->proto_version);

	switch (c->proto_version) {
	case p9_proto_2000L:
		req = p9_client_rpc(c, P9_TVERSION, "ds",
					c->msize, "9P2000.L");
		break;
	case p9_proto_2000u:
		req = p9_client_rpc(c, P9_TVERSION, "ds",
					c->msize, "9P2000.u");
		break;
	case p9_proto_legacy:
		req = p9_client_rpc(c, P9_TVERSION, "ds",
					c->msize, "9P2000");
		break;
	default:
		return -EINVAL;
	}

	if (IS_ERR(req))
		return PTR_ERR(req);

	err = p9pdu_readf(&req->rc, c->proto_version, "ds", &msize, &version);
	if (err) {
		p9_debug(P9_DEBUG_9P, "version error %d\n", err);
		trace_9p_protocol_dump(c, &req->rc);
		goto error;
	}

	p9_debug(P9_DEBUG_9P, "<<< RVERSION msize %d %s\n", msize, version);
	if (!strncmp(version, "9P2000.L", 8))
		c->proto_version = p9_proto_2000L;
	else if (!strncmp(version, "9P2000.u", 8))
		c->proto_version = p9_proto_2000u;
	else if (!strncmp(version, "9P2000", 6))
		c->proto_version = p9_proto_legacy;
	else {
		p9_debug(P9_DEBUG_ERROR,
			 "server returned an unknown version: %s\n", version);
		err = -EREMOTEIO;
		goto error;
	}

	if (msize < 4096) {
		p9_debug(P9_DEBUG_ERROR,
			 "server returned a msize < 4096: %d\n", msize);
		err = -EREMOTEIO;
		goto error;
	}
	if (msize < c->msize)
		c->msize = msize;

error:
	kfree(version);
	p9_tag_remove(c, req);

	return err;
}