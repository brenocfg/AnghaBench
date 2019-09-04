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
struct mwifiex_private {int dummy; } ;
struct mwifiex_ds_get_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_GET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_GET_LOG ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ds_get_stats*,int) ; 

int
mwifiex_get_stats_info(struct mwifiex_private *priv,
		       struct mwifiex_ds_get_stats *log)
{
	return mwifiex_send_cmd(priv, HostCmd_CMD_802_11_GET_LOG,
				HostCmd_ACT_GEN_GET, 0, log, true);
}