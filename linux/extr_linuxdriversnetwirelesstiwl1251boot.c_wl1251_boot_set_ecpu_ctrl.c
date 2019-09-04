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
typedef  int /*<<< orphan*/  u32 ;
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_REG_ECPU_CONTROL ; 
 int /*<<< orphan*/  wl1251_reg_read32 (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl1251_boot_set_ecpu_ctrl(struct wl1251 *wl, u32 flag)
{
	u32 cpu_ctrl;

	/* 10.5.0 run the firmware (I) */
	cpu_ctrl = wl1251_reg_read32(wl, ACX_REG_ECPU_CONTROL);

	/* 10.5.1 run the firmware (II) */
	cpu_ctrl &= ~flag;
	wl1251_reg_write32(wl, ACX_REG_ECPU_CONTROL, cpu_ctrl);
}