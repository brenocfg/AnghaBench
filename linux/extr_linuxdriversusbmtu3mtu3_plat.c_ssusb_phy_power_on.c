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
struct ssusb_mtk {int num_phys; int /*<<< orphan*/ * phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssusb_phy_power_on(struct ssusb_mtk *ssusb)
{
	int i;
	int ret;

	for (i = 0; i < ssusb->num_phys; i++) {
		ret = phy_power_on(ssusb->phys[i]);
		if (ret)
			goto power_off_phy;
	}
	return 0;

power_off_phy:
	for (; i > 0; i--)
		phy_power_off(ssusb->phys[i - 1]);

	return ret;
}