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
struct fsg_lun {scalar_t__ state; scalar_t__ free_storage_on_release; int /*<<< orphan*/  fsg_num_buffers; int /*<<< orphan*/  buffhds; int /*<<< orphan*/  dev; struct fsg_lun** luns; int /*<<< orphan*/  thread_notifier; } ;
struct fsg_common {scalar_t__ state; scalar_t__ free_storage_on_release; int /*<<< orphan*/  fsg_num_buffers; int /*<<< orphan*/  buffhds; int /*<<< orphan*/  dev; struct fsg_common** luns; int /*<<< orphan*/  thread_notifier; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fsg_lun**) ; 
 int /*<<< orphan*/  FSG_STATE_EXIT ; 
 scalar_t__ FSG_STATE_TERMINATED ; 
 int /*<<< orphan*/  _fsg_common_free_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsg_lun_close (struct fsg_lun*) ; 
 int /*<<< orphan*/  kfree (struct fsg_lun*) ; 
 int /*<<< orphan*/  raise_exception (struct fsg_lun*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsg_common_release(struct fsg_common *common)
{
	int i;

	/* If the thread isn't already dead, tell it to exit now */
	if (common->state != FSG_STATE_TERMINATED) {
		raise_exception(common, FSG_STATE_EXIT);
		wait_for_completion(&common->thread_notifier);
	}

	for (i = 0; i < ARRAY_SIZE(common->luns); ++i) {
		struct fsg_lun *lun = common->luns[i];
		if (!lun)
			continue;
		fsg_lun_close(lun);
		if (device_is_registered(&lun->dev))
			device_unregister(&lun->dev);
		kfree(lun);
	}

	_fsg_common_free_buffers(common->buffhds, common->fsg_num_buffers);
	if (common->free_storage_on_release)
		kfree(common);
}