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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_tdls_stop_cs_params {int /*<<< orphan*/  peer_mac; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT_TDLS_CS_STOP ; 
 int /*<<< orphan*/  HostCmd_CMD_TDLS_CONFIG ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_tdls_stop_cs_params*,int) ; 

int mwifiex_stop_tdls_cs(struct mwifiex_private *priv, const u8 *peer_mac)
{
	struct mwifiex_tdls_stop_cs_params stop_tdls_cs_params;

	ether_addr_copy(stop_tdls_cs_params.peer_mac, peer_mac);

	return mwifiex_send_cmd(priv, HostCmd_CMD_TDLS_CONFIG,
				ACT_TDLS_CS_STOP, 0,
				&stop_tdls_cs_params, true);
}