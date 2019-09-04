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
struct sfp {unsigned int state; } ;

/* Variables and functions */
 unsigned int SFP_F_TX_DISABLE ; 
 int /*<<< orphan*/  T_RESET_US ; 
 int /*<<< orphan*/  sfp_set_state (struct sfp*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfp_module_tx_fault_reset(struct sfp *sfp)
{
	unsigned int state = sfp->state;

	if (state & SFP_F_TX_DISABLE)
		return;

	sfp_set_state(sfp, state | SFP_F_TX_DISABLE);

	udelay(T_RESET_US);

	sfp_set_state(sfp, state);
}