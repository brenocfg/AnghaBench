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
struct dasd_eckd_private {scalar_t__ fcx_max_data; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;

/* Variables and functions */

__attribute__((used)) static int dasd_eckd_hpf_enabled(struct dasd_device *device)
{
	struct dasd_eckd_private *private = device->private;

	return private->fcx_max_data ? 1 : 0;
}