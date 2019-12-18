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
struct p9_req_t {int dummy; } ;
struct p9_fid {int /*<<< orphan*/  fid; struct p9_client* clnt; } ;
struct p9_client {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ IS_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_TREMOVE ; 
 int PTR_ERR (struct p9_req_t*) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 struct p9_req_t* p9_client_rpc (struct p9_client*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_fid_destroy (struct p9_fid*) ; 
 int /*<<< orphan*/  p9_tag_remove (struct p9_client*,struct p9_req_t*) ; 

int p9_client_remove(struct p9_fid *fid)
{
	int err;
	struct p9_client *clnt;
	struct p9_req_t *req;

	p9_debug(P9_DEBUG_9P, ">>> TREMOVE fid %d\n", fid->fid);
	err = 0;
	clnt = fid->clnt;

	req = p9_client_rpc(clnt, P9_TREMOVE, "d", fid->fid);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto error;
	}

	p9_debug(P9_DEBUG_9P, "<<< RREMOVE fid %d\n", fid->fid);

	p9_tag_remove(clnt, req);
error:
	if (err == -ERESTARTSYS)
		p9_client_clunk(fid);
	else
		p9_fid_destroy(fid);
	return err;
}