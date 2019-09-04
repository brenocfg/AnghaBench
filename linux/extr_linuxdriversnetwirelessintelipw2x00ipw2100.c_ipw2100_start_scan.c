#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipw2100_priv {int status; TYPE_1__* ieee; } ;
struct host_command {int host_command_length; scalar_t__* host_command_parameters; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;
struct TYPE_2__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_SCAN ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_SCAN (char*) ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int STATUS_SCANNING ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 

__attribute__((used)) static int ipw2100_start_scan(struct ipw2100_priv *priv)
{
	struct host_command cmd = {
		.host_command = BROADCAST_SCAN,
		.host_command_sequence = 0,
		.host_command_length = 4
	};
	int err;

	IPW_DEBUG_HC("START_SCAN\n");

	cmd.host_command_parameters[0] = 0;

	/* No scanning if in monitor mode */
	if (priv->ieee->iw_mode == IW_MODE_MONITOR)
		return 1;

	if (priv->status & STATUS_SCANNING) {
		IPW_DEBUG_SCAN("Scan requested while already in scan...\n");
		return 0;
	}

	IPW_DEBUG_INFO("enter\n");

	/* Not clearing here; doing so makes iwlist always return nothing...
	 *
	 * We should modify the table logic to use aging tables vs. clearing
	 * the table on each scan start.
	 */
	IPW_DEBUG_SCAN("starting scan\n");

	priv->status |= STATUS_SCANNING;
	err = ipw2100_hw_send_command(priv, &cmd);
	if (err)
		priv->status &= ~STATUS_SCANNING;

	IPW_DEBUG_INFO("exit\n");

	return err;
}