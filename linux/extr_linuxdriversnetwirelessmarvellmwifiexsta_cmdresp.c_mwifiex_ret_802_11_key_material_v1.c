#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct TYPE_8__ {TYPE_3__ key_param_set; } ;
struct mwifiex_private {int wpa_is_gtk_set; int scan_block; int port_open; TYPE_4__ aes_key; int /*<<< orphan*/  adapter; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key_info; } ;
struct host_cmd_ds_802_11_key_material {TYPE_2__ key_param_set; int /*<<< orphan*/  action; } ;
struct TYPE_5__ {struct host_cmd_ds_802_11_key_material key_material; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  INFO ; 
 int KEY_MCAST ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mwifiex_ret_802_11_key_material_v1(struct mwifiex_private *priv,
					      struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_802_11_key_material *key =
						&resp->params.key_material;

	if (le16_to_cpu(key->action) == HostCmd_ACT_GEN_SET) {
		if ((le16_to_cpu(key->key_param_set.key_info) & KEY_MCAST)) {
			mwifiex_dbg(priv->adapter, INFO,
				    "info: key: GTK is set\n");
			priv->wpa_is_gtk_set = true;
			priv->scan_block = false;
			priv->port_open = true;
		}
	}

	memset(priv->aes_key.key_param_set.key, 0,
	       sizeof(key->key_param_set.key));
	priv->aes_key.key_param_set.key_len = key->key_param_set.key_len;
	memcpy(priv->aes_key.key_param_set.key, key->key_param_set.key,
	       le16_to_cpu(priv->aes_key.key_param_set.key_len));

	return 0;
}