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
typedef  int u32 ;
struct pch_dev {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ts_sel; } ;

/* Variables and functions */
 int PCH_ECS_ETH ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pch_eth_enable_set(struct pch_dev *chip)
{
	u32 val;
	/* SET the eth_enable bit */
	val = ioread32(&chip->regs->ts_sel) | (PCH_ECS_ETH);
	iowrite32(val, (&chip->regs->ts_sel));
}