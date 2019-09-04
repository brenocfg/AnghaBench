#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct r8192_priv {int /*<<< orphan*/  wx_mutex; struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct iw_point {int length; int /*<<< orphan*/  pointer; } ;
struct TYPE_6__ {struct iw_point data; } ;
struct iwreq {TYPE_3__ u; } ;
struct ifreq {int dummy; } ;
struct TYPE_4__ {int key_len; int idx; int /*<<< orphan*/  alg; int /*<<< orphan*/  key; int /*<<< orphan*/  set_tx; } ;
struct TYPE_5__ {TYPE_1__ crypt; } ;
struct ieee_param {TYPE_2__ u; int /*<<< orphan*/  cmd; } ;
struct ieee80211_device {int auth_mode; void* group_key_type; scalar_t__ ap_mac_addr; void* pairwise_key_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EnableHWSecurityConfig8192 (struct net_device*) ; 
 int /*<<< orphan*/  IEEE_CMD_SET_ENCRYPTION ; 
 scalar_t__ IS_ERR (struct ieee_param*) ; 
 void* KEY_TYPE_CCMP ; 
 void* KEY_TYPE_NA ; 
 void* KEY_TYPE_TKIP ; 
 void* KEY_TYPE_WEP104 ; 
 void* KEY_TYPE_WEP40 ; 
 int PTR_ERR (struct ieee_param*) ; 
#define  RTL_IOCTL_WPA_SUPPLICANT 128 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int ieee80211_wpa_supplicant_ioctl (struct ieee80211_device*,struct iw_point*) ; 
 int /*<<< orphan*/  kfree (struct ieee_param*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 struct ieee_param* memdup_user (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setKey (struct net_device*,int,int,void*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rtl8192_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	struct iwreq *wrq = (struct iwreq *)rq;
	int ret = -1;
	struct ieee80211_device *ieee = priv->ieee80211;
	u32 key[4];
	u8 broadcast_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	struct iw_point *p = &wrq->u.data;
	struct ieee_param *ipw = NULL;

	mutex_lock(&priv->wx_mutex);


	if (p->length < sizeof(struct ieee_param) || !p->pointer) {
		ret = -EINVAL;
		goto out;
	}

	ipw = memdup_user(p->pointer, p->length);
	if (IS_ERR(ipw)) {
		ret = PTR_ERR(ipw);
		goto out;
	}

	switch (cmd) {
	case RTL_IOCTL_WPA_SUPPLICANT:
		/* parse here for HW security */
		if (ipw->cmd == IEEE_CMD_SET_ENCRYPTION) {
			if (ipw->u.crypt.set_tx) {
				if (strcmp(ipw->u.crypt.alg, "CCMP") == 0) {
					ieee->pairwise_key_type = KEY_TYPE_CCMP;
				} else if (strcmp(ipw->u.crypt.alg, "TKIP") == 0) {
					ieee->pairwise_key_type = KEY_TYPE_TKIP;
				} else if (strcmp(ipw->u.crypt.alg, "WEP") == 0) {
					if (ipw->u.crypt.key_len == 13)
						ieee->pairwise_key_type = KEY_TYPE_WEP104;
					else if (ipw->u.crypt.key_len == 5)
						ieee->pairwise_key_type = KEY_TYPE_WEP40;
				} else {
					ieee->pairwise_key_type = KEY_TYPE_NA;
				}

				if (ieee->pairwise_key_type) {
					memcpy((u8 *)key, ipw->u.crypt.key, 16);
					EnableHWSecurityConfig8192(dev);
					/* We fill both index entry and 4th
					 * entry for pairwise key as in IPW
					 * interface, adhoc will only get here,
					 * so we need index entry for its
					 * default key serching!
					 */
					setKey(dev, 4, ipw->u.crypt.idx,
					       ieee->pairwise_key_type,
					       (u8 *)ieee->ap_mac_addr,
					       0, key);
					if (ieee->auth_mode != 2)
						setKey(dev, ipw->u.crypt.idx,
						       ipw->u.crypt.idx,
						       ieee->pairwise_key_type,
						       (u8 *)ieee->ap_mac_addr,
						       0, key);
				}
			} else {
				memcpy((u8 *)key, ipw->u.crypt.key, 16);
				if (strcmp(ipw->u.crypt.alg, "CCMP") == 0) {
					ieee->group_key_type = KEY_TYPE_CCMP;
				} else if (strcmp(ipw->u.crypt.alg, "TKIP") == 0) {
					ieee->group_key_type = KEY_TYPE_TKIP;
				} else if (strcmp(ipw->u.crypt.alg, "WEP") == 0) {
					if (ipw->u.crypt.key_len == 13)
						ieee->group_key_type = KEY_TYPE_WEP104;
					else if (ipw->u.crypt.key_len == 5)
						ieee->group_key_type = KEY_TYPE_WEP40;
				} else {
					ieee->group_key_type = KEY_TYPE_NA;
				}

				if (ieee->group_key_type) {
					setKey(dev, ipw->u.crypt.idx,
					       /* KeyIndex */
					       ipw->u.crypt.idx,
					       /* KeyType */
					       ieee->group_key_type,
					       /* MacAddr */
					       broadcast_addr,
					       /* DefaultKey */
					       0,
					       /* KeyContent */
					       key);
				}
			}
		}
		ret = ieee80211_wpa_supplicant_ioctl(priv->ieee80211,
						     &wrq->u.data);
		break;

	default:
		ret = -EOPNOTSUPP;
		break;
	}
	kfree(ipw);
	ipw = NULL;
out:
	mutex_unlock(&priv->wx_mutex);
	return ret;
}