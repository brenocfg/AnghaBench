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
typedef  int u64 ;
struct gx_pll_entry {int sys_rstpll_bits; scalar_t__ dotpll_value; scalar_t__ pixclock; } ;
struct TYPE_3__ {scalar_t__ pixclock; } ;
struct fb_info {TYPE_1__ var; } ;
struct TYPE_4__ {int x86_stepping; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct gx_pll_entry*) ; 
 int /*<<< orphan*/  MSR_GLCP_DOTPLL ; 
 int MSR_GLCP_DOTPLL_BYPASS ; 
 int MSR_GLCP_DOTPLL_DOTRESET ; 
 int MSR_GLCP_DOTPLL_LOCK ; 
 int /*<<< orphan*/  MSR_GLCP_SYS_RSTPLL ; 
 int MSR_GLCP_SYS_RSTPLL_DOTPOSTDIV3 ; 
 int MSR_GLCP_SYS_RSTPLL_DOTPREDIV2 ; 
 int MSR_GLCP_SYS_RSTPLL_DOTPREMULT2 ; 
 long abs (scalar_t__) ; 
 TYPE_2__ cpu_data (int /*<<< orphan*/ ) ; 
 struct gx_pll_entry* gx_pll_table_14MHz ; 
 struct gx_pll_entry* gx_pll_table_48MHz ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

void gx_set_dclk_frequency(struct fb_info *info)
{
	const struct gx_pll_entry *pll_table;
	int pll_table_len;
	int i, best_i;
	long min, diff;
	u64 dotpll, sys_rstpll;
	int timeout = 1000;

	/* Rev. 1 Geode GXs use a 14 MHz reference clock instead of 48 MHz. */
	if (cpu_data(0).x86_stepping == 1) {
		pll_table = gx_pll_table_14MHz;
		pll_table_len = ARRAY_SIZE(gx_pll_table_14MHz);
	} else {
		pll_table = gx_pll_table_48MHz;
		pll_table_len = ARRAY_SIZE(gx_pll_table_48MHz);
	}

	/* Search the table for the closest pixclock. */
	best_i = 0;
	min = abs(pll_table[0].pixclock - info->var.pixclock);
	for (i = 1; i < pll_table_len; i++) {
		diff = abs(pll_table[i].pixclock - info->var.pixclock);
		if (diff < min) {
			min = diff;
			best_i = i;
		}
	}

	rdmsrl(MSR_GLCP_SYS_RSTPLL, sys_rstpll);
	rdmsrl(MSR_GLCP_DOTPLL, dotpll);

	/* Program new M, N and P. */
	dotpll &= 0x00000000ffffffffull;
	dotpll |= (u64)pll_table[best_i].dotpll_value << 32;
	dotpll |= MSR_GLCP_DOTPLL_DOTRESET;
	dotpll &= ~MSR_GLCP_DOTPLL_BYPASS;

	wrmsrl(MSR_GLCP_DOTPLL, dotpll);

	/* Program dividers. */
	sys_rstpll &= ~( MSR_GLCP_SYS_RSTPLL_DOTPREDIV2
			 | MSR_GLCP_SYS_RSTPLL_DOTPREMULT2
			 | MSR_GLCP_SYS_RSTPLL_DOTPOSTDIV3 );
	sys_rstpll |= pll_table[best_i].sys_rstpll_bits;

	wrmsrl(MSR_GLCP_SYS_RSTPLL, sys_rstpll);

	/* Clear reset bit to start PLL. */
	dotpll &= ~(MSR_GLCP_DOTPLL_DOTRESET);
	wrmsrl(MSR_GLCP_DOTPLL, dotpll);

	/* Wait for LOCK bit. */
	do {
		rdmsrl(MSR_GLCP_DOTPLL, dotpll);
	} while (timeout-- && !(dotpll & MSR_GLCP_DOTPLL_LOCK));
}