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
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL18XX_ENABLE ; 
 int /*<<< orphan*/  WL18XX_SPARE_A2 ; 
 int wlcore_write32 (struct wl1271*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wl18xx_boot_soft_reset(struct wl1271 *wl)
{
	int ret;

	/* disable Rx/Tx */
	ret = wlcore_write32(wl, WL18XX_ENABLE, 0x0);
	if (ret < 0)
		goto out;

	/* disable auto calibration on start*/
	ret = wlcore_write32(wl, WL18XX_SPARE_A2, 0xffff);

out:
	return ret;
}