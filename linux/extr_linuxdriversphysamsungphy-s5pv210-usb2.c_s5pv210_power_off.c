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
struct samsung_usb2_phy_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s5pv210_isol (struct samsung_usb2_phy_instance*,int) ; 
 int /*<<< orphan*/  s5pv210_phy_pwr (struct samsung_usb2_phy_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5pv210_power_off(struct samsung_usb2_phy_instance *inst)
{
	s5pv210_phy_pwr(inst, 0);
	s5pv210_isol(inst, 1);

	return 0;
}