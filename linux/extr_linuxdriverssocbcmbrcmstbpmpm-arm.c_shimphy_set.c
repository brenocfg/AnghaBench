#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int num_memc; TYPE_1__* memcs; int /*<<< orphan*/  needs_ddr_pad; } ;
struct TYPE_3__ {scalar_t__ ddr_shimphy_base; } ;

/* Variables and functions */
 scalar_t__ SHIMPHY_DDR_PAD_CNTRL ; 
 TYPE_2__ ctrl ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void shimphy_set(u32 value, u32 mask)
{
	int i;

	if (!ctrl.needs_ddr_pad)
		return;

	for (i = 0; i < ctrl.num_memc; i++) {
		u32 tmp;

		tmp = readl_relaxed(ctrl.memcs[i].ddr_shimphy_base +
			SHIMPHY_DDR_PAD_CNTRL);
		tmp = value | (tmp & mask);
		writel_relaxed(tmp, ctrl.memcs[i].ddr_shimphy_base +
			SHIMPHY_DDR_PAD_CNTRL);
	}
	wmb(); /* Complete sequence in order. */
}