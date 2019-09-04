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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpni_cmd_clear_mac_filters {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_CMDID_CLR_MAC_FILTERS ; 
 int /*<<< orphan*/  MULTICAST_FILTERS ; 
 int /*<<< orphan*/  UNICAST_FILTERS ; 
 int /*<<< orphan*/  dpni_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_clear_mac_filters(struct fsl_mc_io *mc_io,
			   u32 cmd_flags,
			   u16 token,
			   int unicast,
			   int multicast)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_clear_mac_filters *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_CLR_MAC_FILTERS,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_clear_mac_filters *)cmd.params;
	dpni_set_field(cmd_params->flags, UNICAST_FILTERS, unicast);
	dpni_set_field(cmd_params->flags, MULTICAST_FILTERS, multicast);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}