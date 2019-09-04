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
typedef  int u32 ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOT11H_I ; 
 scalar_t__ GET_BSS_ROLE (struct mwifiex_private*) ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_SNMP_MIB ; 
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 int MWIFIEX_MASTER_RADAR_DET_MASK ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int mwifiex_11h_activate(struct mwifiex_private *priv, bool flag)
{
	u32 enable = flag;

	/* enable master mode radar detection on AP interface */
	if ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) && enable)
		enable |= MWIFIEX_MASTER_RADAR_DET_MASK;

	return mwifiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
				HostCmd_ACT_GEN_SET, DOT11H_I, &enable, true);
}