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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  poweroff_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

void apb_ctrl_poweroff(struct device *dev)
{
	poweroff_seq(to_platform_device(dev));
}