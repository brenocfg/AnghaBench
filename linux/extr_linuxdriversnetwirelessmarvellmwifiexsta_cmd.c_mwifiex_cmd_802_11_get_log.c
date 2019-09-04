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
struct host_cmd_ds_command {void* size; void* command; } ;
struct host_cmd_ds_802_11_get_log {int dummy; } ;

/* Variables and functions */
 scalar_t__ HostCmd_CMD_802_11_GET_LOG ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 

__attribute__((used)) static int
mwifiex_cmd_802_11_get_log(struct host_cmd_ds_command *cmd)
{
	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_GET_LOG);
	cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_802_11_get_log) +
				S_DS_GEN);
	return 0;
}