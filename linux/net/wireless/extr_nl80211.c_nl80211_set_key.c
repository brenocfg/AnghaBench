#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_3__* ieee80211_ptr; int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_10__ {scalar_t__ mode; } ;
struct key_parse {scalar_t__ idx; TYPE_5__ p; int /*<<< orphan*/  def_multi; scalar_t__ def_uni; scalar_t__ defmgmt; scalar_t__ def; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_3__* ieee80211_ptr; int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_8__ {scalar_t__ default_key; scalar_t__ default_mgmt_key; } ;
struct TYPE_9__ {TYPE_2__ wext; } ;
struct TYPE_7__ {int /*<<< orphan*/  set_default_mgmt_key; int /*<<< orphan*/  set_default_key; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_MAC ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_EXT_KEY_ID ; 
 int /*<<< orphan*/  NL80211_KEYTYPE_PAIRWISE ; 
 scalar_t__ NL80211_KEY_SET_TX ; 
 int nl80211_key_allowed (TYPE_3__*) ; 
 int nl80211_parse_key (struct genl_info*,struct key_parse*) ; 
 int /*<<< orphan*/ * nla_data (scalar_t__) ; 
 int rdev_add_key (struct net_device*,struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int rdev_set_default_key (struct net_device*,struct net_device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int rdev_set_default_mgmt_key (struct net_device*,struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  wdev_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  wdev_unlock (TYPE_3__*) ; 
 scalar_t__ wiphy_ext_feature_isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_set_key(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct key_parse key;
	int err;
	struct net_device *dev = info->user_ptr[1];

	err = nl80211_parse_key(info, &key);
	if (err)
		return err;

	if (key.idx < 0)
		return -EINVAL;

	/* Only support setting default key and
	 * Extended Key ID action NL80211_KEY_SET_TX.
	 */
	if (!key.def && !key.defmgmt &&
	    !(key.p.mode == NL80211_KEY_SET_TX))
		return -EINVAL;

	wdev_lock(dev->ieee80211_ptr);

	if (key.def) {
		if (!rdev->ops->set_default_key) {
			err = -EOPNOTSUPP;
			goto out;
		}

		err = nl80211_key_allowed(dev->ieee80211_ptr);
		if (err)
			goto out;

		err = rdev_set_default_key(rdev, dev, key.idx,
						 key.def_uni, key.def_multi);

		if (err)
			goto out;

#ifdef CONFIG_CFG80211_WEXT
		dev->ieee80211_ptr->wext.default_key = key.idx;
#endif
	} else if (key.defmgmt) {
		if (key.def_uni || !key.def_multi) {
			err = -EINVAL;
			goto out;
		}

		if (!rdev->ops->set_default_mgmt_key) {
			err = -EOPNOTSUPP;
			goto out;
		}

		err = nl80211_key_allowed(dev->ieee80211_ptr);
		if (err)
			goto out;

		err = rdev_set_default_mgmt_key(rdev, dev, key.idx);
		if (err)
			goto out;

#ifdef CONFIG_CFG80211_WEXT
		dev->ieee80211_ptr->wext.default_mgmt_key = key.idx;
#endif
	} else if (key.p.mode == NL80211_KEY_SET_TX &&
		   wiphy_ext_feature_isset(&rdev->wiphy,
					   NL80211_EXT_FEATURE_EXT_KEY_ID)) {
		u8 *mac_addr = NULL;

		if (info->attrs[NL80211_ATTR_MAC])
			mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

		if (!mac_addr || key.idx < 0 || key.idx > 1) {
			err = -EINVAL;
			goto out;
		}

		err = rdev_add_key(rdev, dev, key.idx,
				   NL80211_KEYTYPE_PAIRWISE,
				   mac_addr, &key.p);
	} else {
		err = -EINVAL;
	}
 out:
	wdev_unlock(dev->ieee80211_ptr);

	return err;
}