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
typedef  int u32 ;
struct p9_req_t {int /*<<< orphan*/  rc; } ;
struct p9_qid {int /*<<< orphan*/  version; scalar_t__ path; int /*<<< orphan*/  type; } ;
struct p9_fid {int mode; int iounit; int /*<<< orphan*/  fid; struct p9_client* clnt; } ;
struct p9_client {int /*<<< orphan*/  proto_version; } ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_TLCREATE ; 
 int PTR_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 
 int p9pdu_readf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct p9_qid*,int*) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,int /*<<< orphan*/ *) ; 

int p9_client_create_dotl(struct p9_fid *ofid, const char *name, u32 flags, u32 mode,
		kgid_t gid, struct p9_qid *qid)
{
	int err = 0;
	struct p9_client *clnt;
	struct p9_req_t *req;
	int iounit;

	p9_debug(P9_DEBUG_9P,
			">>> TLCREATE fid %d name %s flags %d mode %d gid %d\n",
			ofid->fid, name, flags, mode,
		 	from_kgid(&init_user_ns, gid));
	clnt = ofid->clnt;

	if (ofid->mode != -1)
		return -EINVAL;

	req = p9_client_rpc(clnt, P9_TLCREATE, "dsddg", ofid->fid, name, flags,
			mode, gid);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto error;
	}

	err = p9pdu_readf(&req->rc, clnt->proto_version, "Qd", qid, &iounit);
	if (err) {
		trace_9p_protocol_dump(clnt, &req->rc);
		goto free_and_error;
	}

	p9_debug(P9_DEBUG_9P, "<<< RLCREATE qid %x.%llx.%x iounit %x\n",
			qid->type,
			(unsigned long long)qid->path,
			qid->version, iounit);

	ofid->mode = mode;
	ofid->iounit = iounit;

free_and_error:
	p9_tag_remove(clnt, req);
error:
	return err;
}