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
struct host_cmd_ds_802_11_bg_scan_query {int flush; } ;
struct TYPE_2__ {struct host_cmd_ds_802_11_bg_scan_query bg_scan_query; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ HostCmd_CMD_802_11_BG_SCAN_QUERY ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 

int mwifiex_cmd_802_11_bg_scan_query(struct host_cmd_ds_command *cmd)
{
	struct host_cmd_ds_802_11_bg_scan_query *bg_query =
		&cmd->params.bg_scan_query;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_BG_SCAN_QUERY);
	cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_802_11_bg_scan_query)
				+ S_DS_GEN);

	bg_query->flush = 1;

	return 0;
}