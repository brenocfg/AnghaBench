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
struct TYPE_3__ {scalar_t__ e100_base_fx; scalar_t__ e100_base_lx; scalar_t__ e1000_base_t; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct sfp {int sm_retries; TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFP_S_INIT ; 
 int /*<<< orphan*/  T_INIT_JIFFIES ; 
 int /*<<< orphan*/  sfp_module_tx_enable (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_next (struct sfp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_sm_probe_phy (struct sfp*) ; 

__attribute__((used)) static void sfp_sm_mod_init(struct sfp *sfp)
{
	sfp_module_tx_enable(sfp);

	/* Wait t_init before indicating that the link is up, provided the
	 * current state indicates no TX_FAULT.  If TX_FAULT clears before
	 * this time, that's fine too.
	 */
	sfp_sm_next(sfp, SFP_S_INIT, T_INIT_JIFFIES);
	sfp->sm_retries = 5;

	/* Setting the serdes link mode is guesswork: there's no
	 * field in the EEPROM which indicates what mode should
	 * be used.
	 *
	 * If it's a gigabit-only fiber module, it probably does
	 * not have a PHY, so switch to 802.3z negotiation mode.
	 * Otherwise, switch to SGMII mode (which is required to
	 * support non-gigabit speeds) and probe for a PHY.
	 */
	if (sfp->id.base.e1000_base_t ||
	    sfp->id.base.e100_base_lx ||
	    sfp->id.base.e100_base_fx)
		sfp_sm_probe_phy(sfp);
}