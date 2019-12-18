#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cb_stateid; } ;
struct nfsd4_copy {int /*<<< orphan*/  copy_task; TYPE_3__* cp_clp; int /*<<< orphan*/  copies; int /*<<< orphan*/  cp_stateid; TYPE_2__ cp_res; int /*<<< orphan*/  refcount; int /*<<< orphan*/  cp_synchronous; int /*<<< orphan*/  fh; int /*<<< orphan*/  nf_dst; int /*<<< orphan*/  cp_dst_stateid; int /*<<< orphan*/  nf_src; int /*<<< orphan*/  cp_src_stateid; } ;
union nfsd4_op_u {struct nfsd4_copy copy; } ;
struct svc_rqst {int dummy; } ;
struct nfsd_net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fh_handle; } ;
struct nfsd4_compound_state {TYPE_1__ current_fh; TYPE_3__* clp; } ;
struct knfsd_fh {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  async_lock; int /*<<< orphan*/  async_copies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  cleanup_async_copy (struct nfsd4_copy*) ; 
 int /*<<< orphan*/  dup_copy_fields (struct nfsd4_copy*,struct nfsd4_copy*) ; 
 int /*<<< orphan*/  kfree (struct nfsd4_copy*) ; 
 int /*<<< orphan*/  kthread_create (int /*<<< orphan*/ ,struct nfsd4_copy*,char*,char*) ; 
 struct nfsd4_copy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_init_cp_state (struct nfsd_net*,struct nfsd4_copy*) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd4_do_async_copy ; 
 scalar_t__ nfsd4_do_copy (struct nfsd4_copy*,int) ; 
 scalar_t__ nfsd4_verify_copy (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 scalar_t__ nfserrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_copy(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	struct nfsd4_copy *copy = &u->copy;
	__be32 status;
	struct nfsd4_copy *async_copy = NULL;

	status = nfsd4_verify_copy(rqstp, cstate, &copy->cp_src_stateid,
				   &copy->nf_src, &copy->cp_dst_stateid,
				   &copy->nf_dst);
	if (status)
		goto out;

	copy->cp_clp = cstate->clp;
	memcpy(&copy->fh, &cstate->current_fh.fh_handle,
		sizeof(struct knfsd_fh));
	if (!copy->cp_synchronous) {
		struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

		status = nfserrno(-ENOMEM);
		async_copy = kzalloc(sizeof(struct nfsd4_copy), GFP_KERNEL);
		if (!async_copy)
			goto out;
		if (!nfs4_init_cp_state(nn, copy)) {
			kfree(async_copy);
			goto out;
		}
		refcount_set(&async_copy->refcount, 1);
		memcpy(&copy->cp_res.cb_stateid, &copy->cp_stateid,
			sizeof(copy->cp_stateid));
		dup_copy_fields(copy, async_copy);
		async_copy->copy_task = kthread_create(nfsd4_do_async_copy,
				async_copy, "%s", "copy thread");
		if (IS_ERR(async_copy->copy_task))
			goto out_err;
		spin_lock(&async_copy->cp_clp->async_lock);
		list_add(&async_copy->copies,
				&async_copy->cp_clp->async_copies);
		spin_unlock(&async_copy->cp_clp->async_lock);
		wake_up_process(async_copy->copy_task);
		status = nfs_ok;
	} else
		status = nfsd4_do_copy(copy, 1);
out:
	return status;
out_err:
	cleanup_async_copy(async_copy);
	goto out;
}