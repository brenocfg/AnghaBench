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
struct vnt_private {int /*<<< orphan*/  key_entry_inuse; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {int /*<<< orphan*/  hw_key_idx; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
#define  DISABLE_KEY 129 
 int EOPNOTSUPP ; 
#define  SET_KEY 128 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_set_keys (struct ieee80211_hw*,struct ieee80211_sta*,struct ieee80211_vif*,struct ieee80211_key_conf*) ; 

__attribute__((used)) static int vnt_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
		       struct ieee80211_vif *vif, struct ieee80211_sta *sta,
		       struct ieee80211_key_conf *key)
{
	struct vnt_private *priv = hw->priv;

	switch (cmd) {
	case SET_KEY:
		if (vnt_set_keys(hw, sta, vif, key))
			return -EOPNOTSUPP;
		break;
	case DISABLE_KEY:
		if (test_bit(key->hw_key_idx, &priv->key_entry_inuse))
			clear_bit(key->hw_key_idx, &priv->key_entry_inuse);
	default:
		break;
	}

	return 0;
}