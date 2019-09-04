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
struct ieee80211_vif {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ mfp; } ;
struct TYPE_4__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  wowlan; } ;
struct ieee80211_key_conf {int /*<<< orphan*/  flags; int /*<<< orphan*/  key; int /*<<< orphan*/  keylen; int /*<<< orphan*/  keyidx; int /*<<< orphan*/  cipher; } ;
struct ieee80211_key {struct ieee80211_key_conf conf; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ieee80211_key_conf* ERR_CAST (struct ieee80211_key*) ; 
 struct ieee80211_key_conf* ERR_PTR (int) ; 
 int /*<<< orphan*/  IEEE80211_KEY_FLAG_RX_MGMT ; 
 scalar_t__ IEEE80211_MFP_DISABLED ; 
 scalar_t__ IS_ERR (struct ieee80211_key*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 struct ieee80211_key* ieee80211_key_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ieee80211_key_link (struct ieee80211_key*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

struct ieee80211_key_conf *
ieee80211_gtk_rekey_add(struct ieee80211_vif *vif,
			struct ieee80211_key_conf *keyconf)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_key *key;
	int err;

	if (WARN_ON(!local->wowlan))
		return ERR_PTR(-EINVAL);

	if (WARN_ON(vif->type != NL80211_IFTYPE_STATION))
		return ERR_PTR(-EINVAL);

	key = ieee80211_key_alloc(keyconf->cipher, keyconf->keyidx,
				  keyconf->keylen, keyconf->key,
				  0, NULL, NULL);
	if (IS_ERR(key))
		return ERR_CAST(key);

	if (sdata->u.mgd.mfp != IEEE80211_MFP_DISABLED)
		key->conf.flags |= IEEE80211_KEY_FLAG_RX_MGMT;

	err = ieee80211_key_link(key, sdata, NULL);
	if (err)
		return ERR_PTR(err);

	return &key->conf;
}