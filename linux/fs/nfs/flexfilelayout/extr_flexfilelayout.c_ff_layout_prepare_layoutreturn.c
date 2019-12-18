#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs4_layoutreturn_args {TYPE_2__* ld_private; TYPE_1__* inode; int /*<<< orphan*/  range; int /*<<< orphan*/  layout; } ;
struct nfs4_flexfile_layoutreturn_args {int /*<<< orphan*/ * devinfo; int /*<<< orphan*/  num_dev; int /*<<< orphan*/  errors; int /*<<< orphan*/  num_errors; int /*<<< orphan*/ * pages; } ;
struct nfs4_flexfile_layout {int /*<<< orphan*/  generic_hdr; } ;
struct TYPE_4__ {struct nfs4_flexfile_layoutreturn_args* data; int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FF_LAYOUTRETURN_MAXERR ; 
 struct nfs4_flexfile_layout* FF_LAYOUT_FROM_HDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_layout_fetch_ds_ioerr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_layout_mirror_prepare_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs4_flexfile_layoutreturn_args*) ; 
 struct nfs4_flexfile_layoutreturn_args* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layoutreturn_ops ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ff_layout_prepare_layoutreturn(struct nfs4_layoutreturn_args *args)
{
	struct nfs4_flexfile_layoutreturn_args *ff_args;
	struct nfs4_flexfile_layout *ff_layout = FF_LAYOUT_FROM_HDR(args->layout);

	ff_args = kmalloc(sizeof(*ff_args), GFP_KERNEL);
	if (!ff_args)
		goto out_nomem;
	ff_args->pages[0] = alloc_page(GFP_KERNEL);
	if (!ff_args->pages[0])
		goto out_nomem_free;

	INIT_LIST_HEAD(&ff_args->errors);
	ff_args->num_errors = ff_layout_fetch_ds_ioerr(args->layout,
			&args->range, &ff_args->errors,
			FF_LAYOUTRETURN_MAXERR);

	spin_lock(&args->inode->i_lock);
	ff_args->num_dev = ff_layout_mirror_prepare_stats(&ff_layout->generic_hdr,
			&ff_args->devinfo[0], ARRAY_SIZE(ff_args->devinfo));
	spin_unlock(&args->inode->i_lock);

	args->ld_private->ops = &layoutreturn_ops;
	args->ld_private->data = ff_args;
	return 0;
out_nomem_free:
	kfree(ff_args);
out_nomem:
	return -ENOMEM;
}