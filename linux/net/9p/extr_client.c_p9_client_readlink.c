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
struct p9_fid {char* fid; struct p9_client* clnt; } ;
struct p9_client {int /*<<< orphan*/  proto_version; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_TREADLINK ; 
 int PTR_ERR (struct p9_req_t*) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 
 int p9pdu_readf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,int /*<<< orphan*/ *) ; 

int p9_client_readlink(struct p9_fid *fid, char **target)
{
	int err;
	struct p9_client *clnt;
	struct p9_req_t *req;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TREADLINK fid %d\n", fid->fid);

	req = p9_client_rpc(clnt, P9_TREADLINK, "d", fid->fid);
	if (IS_ERR(req))
		return PTR_ERR(req);

	err = p9pdu_readf(&req->rc, clnt->proto_version, "s", target);
	if (err) {
		trace_9p_protocol_dump(clnt, &req->rc);
		goto error;
	}
	p9_debug(P9_DEBUG_9P, "<<< RREADLINK target %s\n", *target);
error:
	p9_tag_remove(clnt, req);
	return err;
}