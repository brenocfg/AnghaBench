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
struct ipw2100_priv {int power_mode; } ;
struct host_command {int host_command_length; int* host_command_parameters; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;

/* Variables and functions */
 int IPW_POWER_ENABLED ; 
 int IPW_POWER_LEVEL (int) ; 
 int IPW_POWER_MODE_CAM ; 
 int /*<<< orphan*/  POWER_MODE ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 

__attribute__((used)) static int ipw2100_set_power_mode(struct ipw2100_priv *priv, int power_level)
{
	struct host_command cmd = {
		.host_command = POWER_MODE,
		.host_command_sequence = 0,
		.host_command_length = 4
	};
	int err;

	cmd.host_command_parameters[0] = power_level;

	err = ipw2100_hw_send_command(priv, &cmd);
	if (err)
		return err;

	if (power_level == IPW_POWER_MODE_CAM)
		priv->power_mode = IPW_POWER_LEVEL(priv->power_mode);
	else
		priv->power_mode = IPW_POWER_ENABLED | power_level;

#ifdef IPW2100_TX_POWER
	if (priv->port_type == IBSS && priv->adhoc_power != DFTL_IBSS_TX_POWER) {
		/* Set beacon interval */
		cmd.host_command = TX_POWER_INDEX;
		cmd.host_command_parameters[0] = (u32) priv->adhoc_power;

		err = ipw2100_hw_send_command(priv, &cmd);
		if (err)
			return err;
	}
#endif

	return 0;
}