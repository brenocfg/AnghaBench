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
struct nfs4_xdr_opaque_data {struct nfs4_flexfile_layoutreturn_args* data; } ;
struct nfs4_flexfile_layoutreturn_args {int /*<<< orphan*/ * pages; int /*<<< orphan*/  num_dev; int /*<<< orphan*/  devinfo; int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_layout_free_ds_ioerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_layout_free_iostats_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs4_flexfile_layoutreturn_args*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ff_layout_free_layoutreturn(struct nfs4_xdr_opaque_data *args)
{
	struct nfs4_flexfile_layoutreturn_args *ff_args;

	if (!args->data)
		return;
	ff_args = args->data;
	args->data = NULL;

	ff_layout_free_ds_ioerr(&ff_args->errors);
	ff_layout_free_iostats_array(ff_args->devinfo, ff_args->num_dev);

	put_page(ff_args->pages[0]);
	kfree(ff_args);
}