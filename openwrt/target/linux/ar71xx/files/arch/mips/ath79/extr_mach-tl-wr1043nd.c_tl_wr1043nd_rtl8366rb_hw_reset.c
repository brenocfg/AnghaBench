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
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_RESET_GE0_PHY ; 
 int /*<<< orphan*/  ath79_device_reset_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_device_reset_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tl_wr1043nd_rtl8366rb_hw_reset(struct rtl8366_smi *smi, bool active)
{
	if (active)
		ath79_device_reset_set(AR71XX_RESET_GE0_PHY);
	else
		ath79_device_reset_clear(AR71XX_RESET_GE0_PHY);
}