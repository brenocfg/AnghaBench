#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ linear_tbl1_addr; scalar_t__ linear_tbl0_addr; } ;
struct vpfe_isif_device {TYPE_1__ isif_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
isif_regw_lin_tbl(struct vpfe_isif_device *isif, u32 val, u32 offset, int i)
{
	if (!i)
		writel(val, isif->isif_cfg.linear_tbl0_addr + offset);
	else
		writel(val, isif->isif_cfg.linear_tbl1_addr + offset);
}