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
struct iwl_rxon_context {int /*<<< orphan*/ * wep_keys; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; } ;
struct ieee80211_key_conf {size_t keyidx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_WEP (struct iwl_priv*,char*,...) ; 
 scalar_t__ iwl_is_rfkill (struct iwl_priv*) ; 
 int iwl_send_static_wepkey_cmd (struct iwl_priv*,struct iwl_rxon_context*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int iwl_remove_default_wep_key(struct iwl_priv *priv,
			       struct iwl_rxon_context *ctx,
			       struct ieee80211_key_conf *keyconf)
{
	int ret;

	lockdep_assert_held(&priv->mutex);

	IWL_DEBUG_WEP(priv, "Removing default WEP key: idx=%d\n",
		      keyconf->keyidx);

	memset(&ctx->wep_keys[keyconf->keyidx], 0, sizeof(ctx->wep_keys[0]));
	if (iwl_is_rfkill(priv)) {
		IWL_DEBUG_WEP(priv,
			"Not sending REPLY_WEPKEY command due to RFKILL.\n");
		/* but keys in device are clear anyway so return success */
		return 0;
	}
	ret = iwl_send_static_wepkey_cmd(priv, ctx, 1);
	IWL_DEBUG_WEP(priv, "Remove default WEP key: idx=%d ret=%d\n",
		      keyconf->keyidx, ret);

	return ret;
}