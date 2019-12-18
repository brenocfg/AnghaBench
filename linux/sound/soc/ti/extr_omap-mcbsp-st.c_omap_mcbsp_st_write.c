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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct omap_mcbsp {TYPE_1__* st_data; } ;
struct TYPE_2__ {scalar_t__ io_base_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void omap_mcbsp_st_write(struct omap_mcbsp *mcbsp, u16 reg, u32 val)
{
	writel_relaxed(val, mcbsp->st_data->io_base_st + reg);
}