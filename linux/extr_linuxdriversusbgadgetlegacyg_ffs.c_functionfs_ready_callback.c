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
struct ffs_data {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  gfs_driver ; 
 int gfs_registered ; 
 scalar_t__ missing_funcs ; 
 scalar_t__ unlikely (int) ; 
 int usb_composite_probe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int functionfs_ready_callback(struct ffs_data *ffs)
{
	int ret = 0;

	if (--missing_funcs)
		return 0;

	if (gfs_registered)
		return -EBUSY;

	gfs_registered = true;

	ret = usb_composite_probe(&gfs_driver);
	if (unlikely(ret < 0)) {
		++missing_funcs;
		gfs_registered = false;
	}

	return ret;
}