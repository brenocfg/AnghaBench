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
struct sfp {int state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SFP_F_TX_DISABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_set_state (struct sfp*,int) ; 

__attribute__((used)) static void sfp_module_tx_enable(struct sfp *sfp)
{
	dev_dbg(sfp->dev, "tx disable %u -> %u\n",
		sfp->state & SFP_F_TX_DISABLE ? 1 : 0, 0);
	sfp->state &= ~SFP_F_TX_DISABLE;
	sfp_set_state(sfp, sfp->state);
}