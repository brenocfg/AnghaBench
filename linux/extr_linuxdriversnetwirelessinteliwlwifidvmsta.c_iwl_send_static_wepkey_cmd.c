#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_wep_key {int dummy; } ;
struct iwl_wep_cmd {int num_keys; int /*<<< orphan*/  global_key_type; TYPE_1__* key; } ;
struct iwl_rxon_context {TYPE_2__* wep_keys; int /*<<< orphan*/  wep_key_cmd; } ;
struct iwl_priv {int dummy; } ;
struct iwl_host_cmd {size_t* len; int /*<<< orphan*/  data; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {scalar_t__ key_size; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int key_index; int key_offset; int /*<<< orphan*/ * key; scalar_t__ key_size; } ;

/* Variables and functions */
 int WEP_INVALID_OFFSET ; 
 int WEP_KEYS_MAX ; 
 int /*<<< orphan*/  WEP_KEY_WEP_TYPE ; 
 int iwl_dvm_send_cmd (struct iwl_priv*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct iwl_wep_cmd*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  might_sleep () ; 

__attribute__((used)) static int iwl_send_static_wepkey_cmd(struct iwl_priv *priv,
				      struct iwl_rxon_context *ctx,
				      bool send_if_empty)
{
	int i, not_empty = 0;
	u8 buff[sizeof(struct iwl_wep_cmd) +
		sizeof(struct iwl_wep_key) * WEP_KEYS_MAX];
	struct iwl_wep_cmd *wep_cmd = (struct iwl_wep_cmd *)buff;
	size_t cmd_size  = sizeof(struct iwl_wep_cmd);
	struct iwl_host_cmd cmd = {
		.id = ctx->wep_key_cmd,
		.data = { wep_cmd, },
	};

	might_sleep();

	memset(wep_cmd, 0, cmd_size +
			(sizeof(struct iwl_wep_key) * WEP_KEYS_MAX));

	for (i = 0; i < WEP_KEYS_MAX ; i++) {
		wep_cmd->key[i].key_index = i;
		if (ctx->wep_keys[i].key_size) {
			wep_cmd->key[i].key_offset = i;
			not_empty = 1;
		} else {
			wep_cmd->key[i].key_offset = WEP_INVALID_OFFSET;
		}

		wep_cmd->key[i].key_size = ctx->wep_keys[i].key_size;
		memcpy(&wep_cmd->key[i].key[3], ctx->wep_keys[i].key,
				ctx->wep_keys[i].key_size);
	}

	wep_cmd->global_key_type = WEP_KEY_WEP_TYPE;
	wep_cmd->num_keys = WEP_KEYS_MAX;

	cmd_size += sizeof(struct iwl_wep_key) * WEP_KEYS_MAX;

	cmd.len[0] = cmd_size;

	if (not_empty || send_if_empty)
		return iwl_dvm_send_cmd(priv, &cmd);
	else
		return 0;
}