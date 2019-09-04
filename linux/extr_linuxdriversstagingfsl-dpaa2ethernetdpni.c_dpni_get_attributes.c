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
struct dpni_rsp_get_attr {int /*<<< orphan*/  wriop_version; int /*<<< orphan*/  fs_key_size; int /*<<< orphan*/  qos_key_size; int /*<<< orphan*/  fs_entries; int /*<<< orphan*/  qos_entries; int /*<<< orphan*/  vlan_filter_entries; int /*<<< orphan*/  mac_filter_entries; int /*<<< orphan*/  num_tcs; int /*<<< orphan*/  num_queues; int /*<<< orphan*/  options; } ;
struct dpni_attr {void* wriop_version; int /*<<< orphan*/  fs_key_size; int /*<<< orphan*/  qos_key_size; void* fs_entries; int /*<<< orphan*/  qos_entries; int /*<<< orphan*/  vlan_filter_entries; int /*<<< orphan*/  mac_filter_entries; int /*<<< orphan*/  num_tcs; int /*<<< orphan*/  num_queues; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_CMDID_GET_ATTR ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_get_attributes(struct fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			struct dpni_attr *attr)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_rsp_get_attr *rsp_params;

	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_GET_ATTR,
					  cmd_flags,
					  token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpni_rsp_get_attr *)cmd.params;
	attr->options = le32_to_cpu(rsp_params->options);
	attr->num_queues = rsp_params->num_queues;
	attr->num_tcs = rsp_params->num_tcs;
	attr->mac_filter_entries = rsp_params->mac_filter_entries;
	attr->vlan_filter_entries = rsp_params->vlan_filter_entries;
	attr->qos_entries = rsp_params->qos_entries;
	attr->fs_entries = le16_to_cpu(rsp_params->fs_entries);
	attr->qos_key_size = rsp_params->qos_key_size;
	attr->fs_key_size = rsp_params->fs_key_size;
	attr->wriop_version = le16_to_cpu(rsp_params->wriop_version);

	return 0;
}