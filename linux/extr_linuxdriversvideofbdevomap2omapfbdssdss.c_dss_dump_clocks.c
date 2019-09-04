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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dss_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DSS_CLK_SRC_FCK ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__ dss ; 
 char* dss_feat_get_clk_source_name (int /*<<< orphan*/ ) ; 
 char* dss_get_generic_clk_source_name (int /*<<< orphan*/ ) ; 
 scalar_t__ dss_runtime_get () ; 
 int /*<<< orphan*/  dss_runtime_put () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

void dss_dump_clocks(struct seq_file *s)
{
	const char *fclk_name, *fclk_real_name;
	unsigned long fclk_rate;

	if (dss_runtime_get())
		return;

	seq_printf(s, "- DSS -\n");

	fclk_name = dss_get_generic_clk_source_name(OMAP_DSS_CLK_SRC_FCK);
	fclk_real_name = dss_feat_get_clk_source_name(OMAP_DSS_CLK_SRC_FCK);
	fclk_rate = clk_get_rate(dss.dss_clk);

	seq_printf(s, "%s (%s) = %lu\n",
			fclk_name, fclk_real_name,
			fclk_rate);

	dss_runtime_put();
}