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
typedef  scalar_t__ u32 ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_SNMP_MIB ; 
 scalar_t__ MWIFIEX_RTS_MAX_VALUE ; 
 scalar_t__ MWIFIEX_RTS_MIN_VALUE ; 
 int /*<<< orphan*/  RTS_THRESH_I ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int
mwifiex_set_rts(struct mwifiex_private *priv, u32 rts_thr)
{
	if (rts_thr < MWIFIEX_RTS_MIN_VALUE || rts_thr > MWIFIEX_RTS_MAX_VALUE)
		rts_thr = MWIFIEX_RTS_MAX_VALUE;

	return mwifiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
				HostCmd_ACT_GEN_SET, RTS_THRESH_I,
				&rts_thr, true);
}