#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct p9_req_t {int /*<<< orphan*/  rc; } ;
struct p9_fid {int iounit; int /*<<< orphan*/  fid; struct p9_client* clnt; } ;
struct p9_client {int msize; int /*<<< orphan*/  proto_version; TYPE_1__* trans_mod; } ;
struct kvec {char* iov_base; int iov_len; } ;
struct iov_iter {int dummy; } ;
struct TYPE_2__ {scalar_t__ zc_request; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int P9_READDIRHDRSZ ; 
 int /*<<< orphan*/  P9_TREADDIR ; 
 int PTR_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec*,int,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct p9_req_t* p9_client_zc_rpc (struct p9_client*,int /*<<< orphan*/ ,struct iov_iter*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 
 int p9pdu_readf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int*,char**) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  trace_9p_protocol_dump (struct p9_client*,int /*<<< orphan*/ *) ; 

int p9_client_readdir(struct p9_fid *fid, char *data, u32 count, u64 offset)
{
	int err, rsize, non_zc = 0;
	struct p9_client *clnt;
	struct p9_req_t *req;
	char *dataptr;
	struct kvec kv = {.iov_base = data, .iov_len = count};
	struct iov_iter to;

	iov_iter_kvec(&to, READ, &kv, 1, count);

	p9_debug(P9_DEBUG_9P, ">>> TREADDIR fid %d offset %llu count %d\n",
				fid->fid, (unsigned long long) offset, count);

	err = 0;
	clnt = fid->clnt;

	rsize = fid->iounit;
	if (!rsize || rsize > clnt->msize-P9_READDIRHDRSZ)
		rsize = clnt->msize - P9_READDIRHDRSZ;

	if (count < rsize)
		rsize = count;

	/* Don't bother zerocopy for small IO (< 1024) */
	if (clnt->trans_mod->zc_request && rsize > 1024) {
		/*
		 * response header len is 11
		 * PDU Header(7) + IO Size (4)
		 */
		req = p9_client_zc_rpc(clnt, P9_TREADDIR, &to, NULL, rsize, 0,
				       11, "dqd", fid->fid, offset, rsize);
	} else {
		non_zc = 1;
		req = p9_client_rpc(clnt, P9_TREADDIR, "dqd", fid->fid,
				    offset, rsize);
	}
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto error;
	}

	err = p9pdu_readf(&req->rc, clnt->proto_version, "D", &count, &dataptr);
	if (err) {
		trace_9p_protocol_dump(clnt, &req->rc);
		goto free_and_error;
	}
	if (rsize < count) {
		pr_err("bogus RREADDIR count (%d > %d)\n", count, rsize);
		count = rsize;
	}

	p9_debug(P9_DEBUG_9P, "<<< RREADDIR count %d\n", count);

	if (non_zc)
		memmove(data, dataptr, count);

	p9_tag_remove(clnt, req);
	return count;

free_and_error:
	p9_tag_remove(clnt, req);
error:
	return err;
}