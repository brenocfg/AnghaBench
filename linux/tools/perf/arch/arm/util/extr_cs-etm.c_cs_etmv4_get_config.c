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
typedef  int u64 ;
struct auxtrace_record {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETM4_CFG_BIT_CTXTID ; 
 int /*<<< orphan*/  ETM4_CFG_BIT_CYCACC ; 
 int /*<<< orphan*/  ETM4_CFG_BIT_RETSTK ; 
 int /*<<< orphan*/  ETM4_CFG_BIT_TS ; 
 int /*<<< orphan*/  ETM_OPT_CTXTID ; 
 int /*<<< orphan*/  ETM_OPT_CYCACC ; 
 int /*<<< orphan*/  ETM_OPT_RETSTK ; 
 int /*<<< orphan*/  ETM_OPT_TS ; 
 int cs_etm_get_config (struct auxtrace_record*) ; 

__attribute__((used)) static u64 cs_etmv4_get_config(struct auxtrace_record *itr)
{
	u64 config = 0;
	u64 config_opts = 0;

	/*
	 * The perf event variable config bits represent both
	 * the command line options and register programming
	 * bits in ETMv3/PTM. For ETMv4 we must remap options
	 * to real bits
	 */
	config_opts = cs_etm_get_config(itr);
	if (config_opts & BIT(ETM_OPT_CYCACC))
		config |= BIT(ETM4_CFG_BIT_CYCACC);
	if (config_opts & BIT(ETM_OPT_CTXTID))
		config |= BIT(ETM4_CFG_BIT_CTXTID);
	if (config_opts & BIT(ETM_OPT_TS))
		config |= BIT(ETM4_CFG_BIT_TS);
	if (config_opts & BIT(ETM_OPT_RETSTK))
		config |= BIT(ETM4_CFG_BIT_RETSTK);

	return config;
}