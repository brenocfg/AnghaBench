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
struct nfsd4_copy {int /*<<< orphan*/  cp_cb; int /*<<< orphan*/  cp_clp; int /*<<< orphan*/  fh; int /*<<< orphan*/  nfserr; int /*<<< orphan*/  cp_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFSPROC4_CLNT_CB_OFFLOAD ; 
 int /*<<< orphan*/  cleanup_async_copy (struct nfsd4_copy*) ; 
 struct nfsd4_copy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfsd4_cb_offload_ops ; 
 int /*<<< orphan*/  nfsd4_do_copy (struct nfsd4_copy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_init_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_run_cb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfsd4_do_async_copy(void *data)
{
	struct nfsd4_copy *copy = (struct nfsd4_copy *)data;
	struct nfsd4_copy *cb_copy;

	copy->nfserr = nfsd4_do_copy(copy, 0);
	cb_copy = kzalloc(sizeof(struct nfsd4_copy), GFP_KERNEL);
	if (!cb_copy)
		goto out;
	memcpy(&cb_copy->cp_res, &copy->cp_res, sizeof(copy->cp_res));
	cb_copy->cp_clp = copy->cp_clp;
	cb_copy->nfserr = copy->nfserr;
	memcpy(&cb_copy->fh, &copy->fh, sizeof(copy->fh));
	nfsd4_init_cb(&cb_copy->cp_cb, cb_copy->cp_clp,
			&nfsd4_cb_offload_ops, NFSPROC4_CLNT_CB_OFFLOAD);
	nfsd4_run_cb(&cb_copy->cp_cb);
out:
	cleanup_async_copy(copy);
	return 0;
}