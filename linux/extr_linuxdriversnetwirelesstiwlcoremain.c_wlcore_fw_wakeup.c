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
 int /*<<< orphan*/  ELPCTRL_WAKE_UP ; 
 int /*<<< orphan*/  HW_ACCESS_ELP_CTRL_REG ; 
 int wlcore_raw_write32 (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wlcore_fw_wakeup(struct wl1271 *wl)
{
	return wlcore_raw_write32(wl, HW_ACCESS_ELP_CTRL_REG, ELPCTRL_WAKE_UP);
}