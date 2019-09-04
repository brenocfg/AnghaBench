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
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char const* dev_name (int /*<<< orphan*/ ) ; 

const char *pinctrl_dev_get_devname(struct pinctrl_dev *pctldev)
{
	return dev_name(pctldev->dev);
}