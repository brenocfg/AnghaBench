#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfs_writeverf {int dummy; } ;
struct nfs_commitres {TYPE_3__* verf; } ;
struct TYPE_5__ {int /*<<< orphan*/  verifier; } ;
struct TYPE_6__ {TYPE_1__ verifier; int /*<<< orphan*/  count; } ;
struct nfs42_copy_res {TYPE_2__ write_res; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_7__ {int /*<<< orphan*/  verifier; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nfs4_proc_commit (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs_commitres*) ; 
 scalar_t__ nfs_write_verifier_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_copy_commit(struct file *dst, loff_t pos_dst,
			       struct nfs42_copy_res *res)
{
	struct nfs_commitres cres;
	int status = -ENOMEM;

	cres.verf = kzalloc(sizeof(struct nfs_writeverf), GFP_NOFS);
	if (!cres.verf)
		goto out;

	status = nfs4_proc_commit(dst, pos_dst, res->write_res.count, &cres);
	if (status)
		goto out_free;
	if (nfs_write_verifier_cmp(&res->write_res.verifier.verifier,
				    &cres.verf->verifier)) {
		dprintk("commit verf differs from copy verf\n");
		status = -EAGAIN;
	}
out_free:
	kfree(cres.verf);
out:
	return status;
}