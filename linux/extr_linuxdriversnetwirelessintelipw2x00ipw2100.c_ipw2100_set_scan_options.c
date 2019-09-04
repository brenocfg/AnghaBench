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
struct ipw2100_priv {int config; int /*<<< orphan*/  channel_mask; TYPE_2__* ieee; } ;
struct host_command {int host_command_length; int /*<<< orphan*/ * host_command_parameters; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;
struct TYPE_3__ {int flags; scalar_t__ enabled; } ;
struct TYPE_4__ {TYPE_1__ sec; } ;

/* Variables and functions */
 int CFG_ASSOCIATE ; 
 int CFG_PASSIVE_SCAN ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_SCAN (char*) ; 
 int /*<<< orphan*/  IPW_SCAN_MIXED_CELL ; 
 int /*<<< orphan*/  IPW_SCAN_NOASSOCIATE ; 
 int /*<<< orphan*/  IPW_SCAN_PASSIVE ; 
 int SEC_ENABLED ; 
 int /*<<< orphan*/  SET_SCAN_OPTIONS ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 

__attribute__((used)) static int ipw2100_set_scan_options(struct ipw2100_priv *priv)
{
	struct host_command cmd = {
		.host_command = SET_SCAN_OPTIONS,
		.host_command_sequence = 0,
		.host_command_length = 8
	};
	int err;

	IPW_DEBUG_INFO("enter\n");

	IPW_DEBUG_SCAN("setting scan options\n");

	cmd.host_command_parameters[0] = 0;

	if (!(priv->config & CFG_ASSOCIATE))
		cmd.host_command_parameters[0] |= IPW_SCAN_NOASSOCIATE;
	if ((priv->ieee->sec.flags & SEC_ENABLED) && priv->ieee->sec.enabled)
		cmd.host_command_parameters[0] |= IPW_SCAN_MIXED_CELL;
	if (priv->config & CFG_PASSIVE_SCAN)
		cmd.host_command_parameters[0] |= IPW_SCAN_PASSIVE;

	cmd.host_command_parameters[1] = priv->channel_mask;

	err = ipw2100_hw_send_command(priv, &cmd);

	IPW_DEBUG_HC("SET_SCAN_OPTIONS 0x%04X\n",
		     cmd.host_command_parameters[0]);

	return err;
}