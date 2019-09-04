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
struct mwifiex_ds_hs_cfg {int is_invoke_hostcmd; int /*<<< orphan*/  conditions; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS_CFG_CANCEL ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int mwifiex_set_hs_params (struct mwifiex_private*,int /*<<< orphan*/ ,int,struct mwifiex_ds_hs_cfg*) ; 

int mwifiex_cancel_hs(struct mwifiex_private *priv, int cmd_type)
{
	struct mwifiex_ds_hs_cfg hscfg;

	hscfg.conditions = HS_CFG_CANCEL;
	hscfg.is_invoke_hostcmd = true;

	return mwifiex_set_hs_params(priv, HostCmd_ACT_GEN_SET,
				    cmd_type, &hscfg);
}