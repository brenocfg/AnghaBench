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
struct mwifiex_ds_encrypt_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_KEY_MATERIAL ; 
 int /*<<< orphan*/  KEY_INFO_ENABLED ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ds_encrypt_key*,int) ; 

__attribute__((used)) static int mwifiex_sec_ioctl_set_wapi_key(struct mwifiex_private *priv,
			       struct mwifiex_ds_encrypt_key *encrypt_key)
{

	return mwifiex_send_cmd(priv, HostCmd_CMD_802_11_KEY_MATERIAL,
				HostCmd_ACT_GEN_SET, KEY_INFO_ENABLED,
				encrypt_key, true);
}