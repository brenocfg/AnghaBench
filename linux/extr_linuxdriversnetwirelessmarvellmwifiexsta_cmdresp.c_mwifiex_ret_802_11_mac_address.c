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
struct mwifiex_private {int /*<<< orphan*/  curr_addr; int /*<<< orphan*/  adapter; } ;
struct host_cmd_ds_802_11_mac_address {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_2__ {struct host_cmd_ds_802_11_mac_address mac_addr; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_ret_802_11_mac_address(struct mwifiex_private *priv,
					  struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_802_11_mac_address *cmd_mac_addr =
							&resp->params.mac_addr;

	memcpy(priv->curr_addr, cmd_mac_addr->mac_addr, ETH_ALEN);

	mwifiex_dbg(priv->adapter, INFO,
		    "info: set mac address: %pM\n", priv->curr_addr);

	return 0;
}