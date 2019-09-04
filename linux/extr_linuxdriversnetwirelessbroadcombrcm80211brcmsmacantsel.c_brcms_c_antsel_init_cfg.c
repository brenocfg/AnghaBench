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
typedef  void* u8 ;
struct brcms_antselcfg {scalar_t__ num_antcfg; void** ant_config; } ;
struct antsel_info {scalar_t__ antsel_type; scalar_t__ antsel_avail; } ;

/* Variables and functions */
 scalar_t__ ANTSEL_2x3 ; 
 scalar_t__ ANTSEL_2x4 ; 
 int ANT_SELCFG_AUTO ; 
 void* ANT_SELCFG_DEF_2x2 ; 
 int ANT_SELCFG_DEF_2x3 ; 
 void* ANT_SELCFG_DEF_2x4 ; 
 scalar_t__ ANT_SELCFG_NUM_2x3 ; 
 scalar_t__ ANT_SELCFG_NUM_2x4 ; 
 size_t ANT_SELCFG_RX_DEF ; 
 size_t ANT_SELCFG_RX_UNICAST ; 
 size_t ANT_SELCFG_TX_DEF ; 
 size_t ANT_SELCFG_TX_UNICAST ; 

__attribute__((used)) static void
brcms_c_antsel_init_cfg(struct antsel_info *asi, struct brcms_antselcfg *antsel,
		    bool auto_sel)
{
	if (asi->antsel_type == ANTSEL_2x3) {
		u8 antcfg_def = ANT_SELCFG_DEF_2x3 |
		    ((asi->antsel_avail && auto_sel) ? ANT_SELCFG_AUTO : 0);
		antsel->ant_config[ANT_SELCFG_TX_DEF] = antcfg_def;
		antsel->ant_config[ANT_SELCFG_TX_UNICAST] = antcfg_def;
		antsel->ant_config[ANT_SELCFG_RX_DEF] = antcfg_def;
		antsel->ant_config[ANT_SELCFG_RX_UNICAST] = antcfg_def;
		antsel->num_antcfg = ANT_SELCFG_NUM_2x3;

	} else if (asi->antsel_type == ANTSEL_2x4) {

		antsel->ant_config[ANT_SELCFG_TX_DEF] = ANT_SELCFG_DEF_2x4;
		antsel->ant_config[ANT_SELCFG_TX_UNICAST] = ANT_SELCFG_DEF_2x4;
		antsel->ant_config[ANT_SELCFG_RX_DEF] = ANT_SELCFG_DEF_2x4;
		antsel->ant_config[ANT_SELCFG_RX_UNICAST] = ANT_SELCFG_DEF_2x4;
		antsel->num_antcfg = ANT_SELCFG_NUM_2x4;

	} else {		/* no antenna selection available */

		antsel->ant_config[ANT_SELCFG_TX_DEF] = ANT_SELCFG_DEF_2x2;
		antsel->ant_config[ANT_SELCFG_TX_UNICAST] = ANT_SELCFG_DEF_2x2;
		antsel->ant_config[ANT_SELCFG_RX_DEF] = ANT_SELCFG_DEF_2x2;
		antsel->ant_config[ANT_SELCFG_RX_UNICAST] = ANT_SELCFG_DEF_2x2;
		antsel->num_antcfg = 0;
	}
}