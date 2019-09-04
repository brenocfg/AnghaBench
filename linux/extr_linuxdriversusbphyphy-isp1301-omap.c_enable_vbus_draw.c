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
struct isp1301 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void enable_vbus_draw(struct isp1301 *isp, unsigned mA)
{
	/* H4 controls this by DIP switch S2.4; no soft control.
	 * ON means the charger is always enabled.  Leave it OFF
	 * unless the OTG port is used only in B-peripheral mode.
	 */
}