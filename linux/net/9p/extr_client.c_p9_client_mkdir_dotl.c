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
struct p9_qid {int /*<<< orphan*/  version; scalar_t__ path; int /*<<< orphan*/  type; } ;
struct p9_fid {int /*<<< orphan*/  fid; struct p9_client* clnt; } ;
struct p9_client {int /*<<< orphan*/  proto_version; } ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_TMKDIR ; 
 int PTR_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 
 int p9pdu_readf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct p9_qid*) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,int /*<<< orphan*/ *) ; 

int p9_client_mkdir_dotl(struct p9_fid *fid, const char *name, int mode,
				kgid_t gid, struct p9_qid *qid)
{
	int err;
	struct p9_client *clnt;
	struct p9_req_t *req;

	err = 0;
	clnt = fid->clnt;
	p9_debug(P9_DEBUG_9P, ">>> TMKDIR fid %d name %s mode %d gid %d\n",
		 fid->fid, name, mode, from_kgid(&init_user_ns, gid));
	req = p9_client_rpc(clnt, P9_TMKDIR, "dsdg", fid->fid, name, mode,
		gid);
	if (IS_ERR(req))
		return PTR_ERR(req);

	err = p9pdu_readf(&req->rc, clnt->proto_version, "Q", qid);
	if (err) {
		trace_9p_protocol_dump(clnt, &req->rc);
		goto error;
	}
	p9_debug(P9_DEBUG_9P, "<<< RMKDIR qid %x.%llx.%x\n", qid->type,
				(unsigned long long)qid->path, qid->version);

error:
	p9_tag_remove(clnt, req);
	return err;

}