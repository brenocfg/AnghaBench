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
struct ffs_data {scalar_t__ setup_state; void* state; int /*<<< orphan*/  opened; int /*<<< orphan*/ * epfiles; int /*<<< orphan*/  eps_count; scalar_t__ no_disconnect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 void* FFS_CLOSING ; 
 void* FFS_DEACTIVATED ; 
 scalar_t__ FFS_SETUP_PENDING ; 
 int /*<<< orphan*/  __ffs_ep0_stall (struct ffs_data*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffs_data_put (struct ffs_data*) ; 
 int /*<<< orphan*/  ffs_data_reset (struct ffs_data*) ; 
 int /*<<< orphan*/  ffs_epfiles_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffs_data_closed(struct ffs_data *ffs)
{
	ENTER();

	if (atomic_dec_and_test(&ffs->opened)) {
		if (ffs->no_disconnect) {
			ffs->state = FFS_DEACTIVATED;
			if (ffs->epfiles) {
				ffs_epfiles_destroy(ffs->epfiles,
						   ffs->eps_count);
				ffs->epfiles = NULL;
			}
			if (ffs->setup_state == FFS_SETUP_PENDING)
				__ffs_ep0_stall(ffs);
		} else {
			ffs->state = FFS_CLOSING;
			ffs_data_reset(ffs);
		}
	}
	if (atomic_read(&ffs->opened) < 0) {
		ffs->state = FFS_CLOSING;
		ffs_data_reset(ffs);
	}

	ffs_data_put(ffs);
}