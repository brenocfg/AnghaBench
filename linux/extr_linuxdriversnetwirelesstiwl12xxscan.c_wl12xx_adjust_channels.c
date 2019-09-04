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
struct wlcore_scan_channels {int /*<<< orphan*/  channels_5; int /*<<< orphan*/  channels_2; int /*<<< orphan*/  passive_active; int /*<<< orphan*/  dfs; int /*<<< orphan*/  active; int /*<<< orphan*/  passive; } ;
struct wl1271_cmd_sched_scan_config {int /*<<< orphan*/  channels_5; int /*<<< orphan*/  channels_2; int /*<<< orphan*/  n_pactive_ch; int /*<<< orphan*/  dfs; int /*<<< orphan*/  active; int /*<<< orphan*/  passive; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wl12xx_adjust_channels(struct wl1271_cmd_sched_scan_config *cmd,
				   struct wlcore_scan_channels *cmd_channels)
{
	memcpy(cmd->passive, cmd_channels->passive, sizeof(cmd->passive));
	memcpy(cmd->active, cmd_channels->active, sizeof(cmd->active));
	cmd->dfs = cmd_channels->dfs;
	cmd->n_pactive_ch = cmd_channels->passive_active;

	memcpy(cmd->channels_2, cmd_channels->channels_2,
	       sizeof(cmd->channels_2));
	memcpy(cmd->channels_5, cmd_channels->channels_5,
	       sizeof(cmd->channels_5));
	/* channels_4 are not supported, so no need to copy them */
}