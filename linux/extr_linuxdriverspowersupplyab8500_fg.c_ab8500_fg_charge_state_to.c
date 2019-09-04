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
struct ab8500_fg {size_t charge_state; int /*<<< orphan*/  dev; } ;
typedef  enum ab8500_fg_charge_state { ____Placeholder_ab8500_fg_charge_state } ab8500_fg_charge_state ;

/* Variables and functions */
 int /*<<< orphan*/ * charge_state ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_fg_charge_state_to(struct ab8500_fg *di,
	enum ab8500_fg_charge_state new_state)
{
	dev_dbg(di->dev, "Charge state from %d [%s] to %d [%s]\n",
		di->charge_state,
		charge_state[di->charge_state],
		new_state,
		charge_state[new_state]);

	di->charge_state = new_state;
}