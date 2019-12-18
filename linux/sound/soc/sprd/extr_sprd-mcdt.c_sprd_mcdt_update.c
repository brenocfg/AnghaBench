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
typedef  int u32 ;
struct sprd_mcdt_dev {int base; } ;

/* Variables and functions */
 int readl_relaxed (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,int) ; 

__attribute__((used)) static void sprd_mcdt_update(struct sprd_mcdt_dev *mcdt, u32 reg, u32 val,
			     u32 mask)
{
	u32 orig = readl_relaxed(mcdt->base + reg);
	u32 tmp;

	tmp = (orig & ~mask) | val;
	writel_relaxed(tmp, mcdt->base + reg);
}