#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;
struct TYPE_11__ {TYPE_2__ aes; } ;
struct TYPE_12__ {TYPE_3__ key_params; } ;
struct TYPE_13__ {TYPE_4__ key_param_set; } ;
struct mwifiex_private {int wpa_is_gtk_set; int scan_block; int port_open; TYPE_5__ aes_key_v2; int /*<<< orphan*/  adapter; } ;
struct TYPE_14__ {int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; } ;
struct TYPE_15__ {TYPE_6__ aes; } ;
struct TYPE_16__ {scalar_t__ key_type; TYPE_7__ key_params; int /*<<< orphan*/  key_info; } ;
struct host_cmd_ds_802_11_key_material_v2 {TYPE_8__ key_param_set; int /*<<< orphan*/  action; } ;
struct TYPE_9__ {struct host_cmd_ds_802_11_key_material_v2 key_material_v2; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  INFO ; 
 int KEY_MCAST ; 
 scalar_t__ KEY_TYPE_ID_AES ; 
 int /*<<< orphan*/  WLAN_KEY_LEN_CCMP ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mwifiex_ret_802_11_key_material_v2(struct mwifiex_private *priv,
					      struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_802_11_key_material_v2 *key_v2;
	__le16 len;

	key_v2 = &resp->params.key_material_v2;
	if (le16_to_cpu(key_v2->action) == HostCmd_ACT_GEN_SET) {
		if ((le16_to_cpu(key_v2->key_param_set.key_info) & KEY_MCAST)) {
			mwifiex_dbg(priv->adapter, INFO, "info: key: GTK is set\n");
			priv->wpa_is_gtk_set = true;
			priv->scan_block = false;
			priv->port_open = true;
		}
	}

	if (key_v2->key_param_set.key_type != KEY_TYPE_ID_AES)
		return 0;

	memset(priv->aes_key_v2.key_param_set.key_params.aes.key, 0,
	       WLAN_KEY_LEN_CCMP);
	priv->aes_key_v2.key_param_set.key_params.aes.key_len =
				key_v2->key_param_set.key_params.aes.key_len;
	len = priv->aes_key_v2.key_param_set.key_params.aes.key_len;
	memcpy(priv->aes_key_v2.key_param_set.key_params.aes.key,
	       key_v2->key_param_set.key_params.aes.key, le16_to_cpu(len));

	return 0;
}