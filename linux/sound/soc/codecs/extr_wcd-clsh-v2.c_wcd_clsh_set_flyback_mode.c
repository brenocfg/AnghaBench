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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int CLS_H_HIFI ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_SUPPLIES ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_DEFAULT ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_MASK ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_UHQA ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wcd_clsh_set_flyback_mode(struct snd_soc_component *comp,
					     int mode)
{
	/* set to HIFI */
	if (mode == CLS_H_HIFI)
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_MASK,
					WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_UHQA);
	else
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_MASK,
					WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_DEFAULT);
}