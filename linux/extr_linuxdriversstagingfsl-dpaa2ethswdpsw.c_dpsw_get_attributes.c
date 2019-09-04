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
struct dpsw_rsp_get_attr {int /*<<< orphan*/  component_type; int /*<<< orphan*/  options; int /*<<< orphan*/  max_meters_per_if; int /*<<< orphan*/  max_fdb_mc_groups; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  dpsw_id; int /*<<< orphan*/  fdb_aging_time; int /*<<< orphan*/  max_fdb_entries; int /*<<< orphan*/  num_vlans; int /*<<< orphan*/  max_vlans; int /*<<< orphan*/  num_fdbs; int /*<<< orphan*/  max_fdbs; int /*<<< orphan*/  num_ifs; } ;
struct dpsw_attr {int /*<<< orphan*/  component_type; int /*<<< orphan*/  options; int /*<<< orphan*/  max_meters_per_if; void* max_fdb_mc_groups; void* mem_size; int /*<<< orphan*/  id; void* fdb_aging_time; void* max_fdb_entries; void* num_vlans; void* max_vlans; int /*<<< orphan*/  num_fdbs; int /*<<< orphan*/  max_fdbs; void* num_ifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPONENT_TYPE ; 
 int /*<<< orphan*/  DPSW_CMDID_GET_ATTR ; 
 int /*<<< orphan*/  dpsw_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpsw_get_attributes(struct fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			struct dpsw_attr *attr)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpsw_rsp_get_attr *rsp_params;
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPSW_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpsw_rsp_get_attr *)cmd.params;
	attr->num_ifs = le16_to_cpu(rsp_params->num_ifs);
	attr->max_fdbs = rsp_params->max_fdbs;
	attr->num_fdbs = rsp_params->num_fdbs;
	attr->max_vlans = le16_to_cpu(rsp_params->max_vlans);
	attr->num_vlans = le16_to_cpu(rsp_params->num_vlans);
	attr->max_fdb_entries = le16_to_cpu(rsp_params->max_fdb_entries);
	attr->fdb_aging_time = le16_to_cpu(rsp_params->fdb_aging_time);
	attr->id = le32_to_cpu(rsp_params->dpsw_id);
	attr->mem_size = le16_to_cpu(rsp_params->mem_size);
	attr->max_fdb_mc_groups = le16_to_cpu(rsp_params->max_fdb_mc_groups);
	attr->max_meters_per_if = rsp_params->max_meters_per_if;
	attr->options = le64_to_cpu(rsp_params->options);
	attr->component_type = dpsw_get_field(rsp_params->component_type,
					      COMPONENT_TYPE);

	return 0;
}