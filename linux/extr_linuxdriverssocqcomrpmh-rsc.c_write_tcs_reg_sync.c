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
typedef  scalar_t__ u32 ;
struct rsc_drv {scalar_t__ tcs_base; } ;

/* Variables and functions */
 int RSC_DRV_TCS_OFFSET ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void write_tcs_reg_sync(struct rsc_drv *drv, int reg, int tcs_id,
			       u32 data)
{
	writel(data, drv->tcs_base + reg + RSC_DRV_TCS_OFFSET * tcs_id);
	for (;;) {
		if (data == readl(drv->tcs_base + reg +
				  RSC_DRV_TCS_OFFSET * tcs_id))
			break;
		udelay(1);
	}
}