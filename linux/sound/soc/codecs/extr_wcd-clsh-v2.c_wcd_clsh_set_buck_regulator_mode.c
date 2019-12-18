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
 int CLS_AB ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_REGULATOR_MODE_CLS_AB ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_REGULATOR_MODE_CLS_H ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_REGULATOR_MODE_MASK ; 
 int /*<<< orphan*/  WCD9XXX_A_ANA_RX_SUPPLIES ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcd_clsh_set_buck_regulator_mode(struct snd_soc_component *comp,
					     int mode)
{
	if (mode == CLS_AB)
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_REGULATOR_MODE_MASK,
					WCD9XXX_A_ANA_RX_REGULATOR_MODE_CLS_AB);
	else
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_REGULATOR_MODE_MASK,
					WCD9XXX_A_ANA_RX_REGULATOR_MODE_CLS_H);
}