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
struct dpsw_fdb_multicast_cfg {int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/  num_ifs; int /*<<< orphan*/  if_id; int /*<<< orphan*/  type; } ;
struct dpsw_cmd_fdb_multicast_op {int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/  if_id; int /*<<< orphan*/  type; void* num_ifs; void* fdb_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSW_CMDID_FDB_ADD_MULTICAST ; 
 int /*<<< orphan*/  ENTRY_TYPE ; 
 int /*<<< orphan*/  build_if_id_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpsw_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpsw_fdb_add_multicast(struct fsl_mc_io *mc_io,
			   u32 cmd_flags,
			   u16 token,
			   u16 fdb_id,
			   const struct dpsw_fdb_multicast_cfg *cfg)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpsw_cmd_fdb_multicast_op *cmd_params;
	int i;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_FDB_ADD_MULTICAST,
					  cmd_flags,
					  token);
	cmd_params = (struct dpsw_cmd_fdb_multicast_op *)cmd.params;
	cmd_params->fdb_id = cpu_to_le16(fdb_id);
	cmd_params->num_ifs = cpu_to_le16(cfg->num_ifs);
	dpsw_set_field(cmd_params->type, ENTRY_TYPE, cfg->type);
	build_if_id_bitmap(cmd_params->if_id, cfg->if_id, cfg->num_ifs);
	for (i = 0; i < 6; i++)
		cmd_params->mac_addr[i] = cfg->mac_addr[5 - i];

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}