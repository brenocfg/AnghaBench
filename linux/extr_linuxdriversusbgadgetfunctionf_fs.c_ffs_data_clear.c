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
struct ffs_data {int /*<<< orphan*/  stringtabs; int /*<<< orphan*/  raw_strings; int /*<<< orphan*/  raw_descs_data; scalar_t__ ffs_eventfd; int /*<<< orphan*/  eps_count; scalar_t__ epfiles; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  eventfd_ctx_put (scalar_t__) ; 
 int /*<<< orphan*/  ffs_closed (struct ffs_data*) ; 
 int /*<<< orphan*/  ffs_epfiles_destroy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffs_data_clear(struct ffs_data *ffs)
{
	ENTER();

	ffs_closed(ffs);

	BUG_ON(ffs->gadget);

	if (ffs->epfiles)
		ffs_epfiles_destroy(ffs->epfiles, ffs->eps_count);

	if (ffs->ffs_eventfd)
		eventfd_ctx_put(ffs->ffs_eventfd);

	kfree(ffs->raw_descs_data);
	kfree(ffs->raw_strings);
	kfree(ffs->stringtabs);
}