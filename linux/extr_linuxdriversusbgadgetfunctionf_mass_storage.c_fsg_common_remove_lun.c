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
struct fsg_lun {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsg_lun_close (struct fsg_lun*) ; 
 int /*<<< orphan*/  kfree (struct fsg_lun*) ; 

void fsg_common_remove_lun(struct fsg_lun *lun)
{
	if (device_is_registered(&lun->dev))
		device_unregister(&lun->dev);
	fsg_lun_close(lun);
	kfree(lun);
}