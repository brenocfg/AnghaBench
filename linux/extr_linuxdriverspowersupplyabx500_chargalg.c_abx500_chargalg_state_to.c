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
struct abx500_chargalg {int charge_state; int /*<<< orphan*/  dev; } ;
typedef  enum abx500_chargalg_states { ____Placeholder_abx500_chargalg_states } abx500_chargalg_states ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * states ; 

__attribute__((used)) static void abx500_chargalg_state_to(struct abx500_chargalg *di,
	enum abx500_chargalg_states state)
{
	dev_dbg(di->dev,
		"State changed: %s (From state: [%d] %s =to=> [%d] %s )\n",
		di->charge_state == state ? "NO" : "YES",
		di->charge_state,
		states[di->charge_state],
		state,
		states[state]);

	di->charge_state = state;
}