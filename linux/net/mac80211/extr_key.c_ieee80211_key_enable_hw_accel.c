#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_4__ sta; int /*<<< orphan*/  uploaded; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;
struct TYPE_11__ {int flags; int cipher; int /*<<< orphan*/  keyidx; } ;
struct ieee80211_key {int flags; TYPE_3__* local; TYPE_5__ conf; struct sta_info* sta; struct ieee80211_sub_if_data* sdata; } ;
struct TYPE_9__ {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  set_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int IEEE80211_KEY_FLAG_PUT_IV_SPACE ; 
 int IEEE80211_KEY_FLAG_PUT_MIC_SPACE ; 
 int IEEE80211_KEY_FLAG_RESERVE_TAILROOM ; 
 int KEY_FLAG_TAINTED ; 
 int KEY_FLAG_UPLOADED_TO_HARDWARE ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 int /*<<< orphan*/  SET_KEY ; 
 int /*<<< orphan*/  SUPPORTS_PER_STA_GTK ; 
 int /*<<< orphan*/  SW_CRYPTO_CONTROL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 138 
#define  WLAN_CIPHER_SUITE_BIP_CMAC_256 137 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_128 136 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_256 135 
#define  WLAN_CIPHER_SUITE_CCMP 134 
#define  WLAN_CIPHER_SUITE_CCMP_256 133 
#define  WLAN_CIPHER_SUITE_GCMP 132 
#define  WLAN_CIPHER_SUITE_GCMP_256 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  assert_key_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  bcast_addr ; 
 int /*<<< orphan*/  decrease_tailroom_need_count (struct ieee80211_sub_if_data*,int) ; 
 int drv_set_key (TYPE_3__*,int /*<<< orphan*/ ,struct ieee80211_sub_if_data*,TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  increment_tailroom_need_count (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  sdata_err (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ieee80211_key_enable_hw_accel(struct ieee80211_key *key)
{
	struct ieee80211_sub_if_data *sdata = key->sdata;
	struct sta_info *sta;
	int ret = -EOPNOTSUPP;

	might_sleep();

	if (key->flags & KEY_FLAG_TAINTED) {
		/* If we get here, it's during resume and the key is
		 * tainted so shouldn't be used/programmed any more.
		 * However, its flags may still indicate that it was
		 * programmed into the device (since we're in resume)
		 * so clear that flag now to avoid trying to remove
		 * it again later.
		 */
		if (key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE &&
		    !(key->conf.flags & (IEEE80211_KEY_FLAG_GENERATE_MMIC |
					 IEEE80211_KEY_FLAG_PUT_MIC_SPACE |
					 IEEE80211_KEY_FLAG_RESERVE_TAILROOM)))
			increment_tailroom_need_count(sdata);

		key->flags &= ~KEY_FLAG_UPLOADED_TO_HARDWARE;
		return -EINVAL;
	}

	if (!key->local->ops->set_key)
		goto out_unsupported;

	assert_key_lock(key->local);

	sta = key->sta;

	/*
	 * If this is a per-STA GTK, check if it
	 * is supported; if not, return.
	 */
	if (sta && !(key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE) &&
	    !ieee80211_hw_check(&key->local->hw, SUPPORTS_PER_STA_GTK))
		goto out_unsupported;

	if (sta && !sta->uploaded)
		goto out_unsupported;

	if (sdata->vif.type == NL80211_IFTYPE_AP_VLAN) {
		/*
		 * The driver doesn't know anything about VLAN interfaces.
		 * Hence, don't send GTKs for VLAN interfaces to the driver.
		 */
		if (!(key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE)) {
			ret = 1;
			goto out_unsupported;
		}
	}

	ret = drv_set_key(key->local, SET_KEY, sdata,
			  sta ? &sta->sta : NULL, &key->conf);

	if (!ret) {
		key->flags |= KEY_FLAG_UPLOADED_TO_HARDWARE;

		if (!(key->conf.flags & (IEEE80211_KEY_FLAG_GENERATE_MMIC |
					 IEEE80211_KEY_FLAG_PUT_MIC_SPACE |
					 IEEE80211_KEY_FLAG_RESERVE_TAILROOM)))
			decrease_tailroom_need_count(sdata, 1);

		WARN_ON((key->conf.flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE) &&
			(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV));

		WARN_ON((key->conf.flags & IEEE80211_KEY_FLAG_PUT_MIC_SPACE) &&
			(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_MMIC));

		return 0;
	}

	if (ret != -ENOSPC && ret != -EOPNOTSUPP && ret != 1)
		sdata_err(sdata,
			  "failed to set key (%d, %pM) to hardware (%d)\n",
			  key->conf.keyidx,
			  sta ? sta->sta.addr : bcast_addr, ret);

 out_unsupported:
	switch (key->conf.cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
	case WLAN_CIPHER_SUITE_TKIP:
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_CCMP_256:
	case WLAN_CIPHER_SUITE_AES_CMAC:
	case WLAN_CIPHER_SUITE_BIP_CMAC_256:
	case WLAN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_CIPHER_SUITE_BIP_GMAC_256:
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
		/* all of these we can do in software - if driver can */
		if (ret == 1)
			return 0;
		if (ieee80211_hw_check(&key->local->hw, SW_CRYPTO_CONTROL))
			return -EINVAL;
		return 0;
	default:
		return -EINVAL;
	}
}