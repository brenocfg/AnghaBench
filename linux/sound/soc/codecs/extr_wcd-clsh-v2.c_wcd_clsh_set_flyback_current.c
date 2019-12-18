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
 int /*<<< orphan*/  WCD9XXX_RX_BIAS_FLYB_BUFF ; 
 int /*<<< orphan*/  WCD9XXX_RX_BIAS_FLYB_VNEG_5_UA_MASK ; 
 int /*<<< orphan*/  WCD9XXX_RX_BIAS_FLYB_VPOS_5_UA_MASK ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void wcd_clsh_set_flyback_current(struct snd_soc_component *comp,
					 int mode)
{

	snd_soc_component_update_bits(comp, WCD9XXX_RX_BIAS_FLYB_BUFF,
				WCD9XXX_RX_BIAS_FLYB_VPOS_5_UA_MASK, 0x0A);
	snd_soc_component_update_bits(comp, WCD9XXX_RX_BIAS_FLYB_BUFF,
				WCD9XXX_RX_BIAS_FLYB_VNEG_5_UA_MASK, 0x0A);
	/* Sleep needed to avoid click and pop as per HW requirement */
	usleep_range(100, 110);
}