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
struct il_priv {int dummy; } ;
struct il_powertable_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  il_build_powertable_cmd (struct il_priv*,struct il_powertable_cmd*) ; 
 int il_power_set_mode (struct il_priv*,struct il_powertable_cmd*,int) ; 

int
il_power_update_mode(struct il_priv *il, bool force)
{
	struct il_powertable_cmd cmd;

	il_build_powertable_cmd(il, &cmd);

	return il_power_set_mode(il, &cmd, force);
}