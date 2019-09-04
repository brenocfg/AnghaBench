#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtl8187_vif {int enable_beacon; int /*<<< orphan*/  beacon_work; struct ieee80211_hw* dev; } ;
struct rtl8187_priv {int /*<<< orphan*/  conf_mutex; TYPE_1__* map; struct ieee80211_vif* vif; } ;
struct ieee80211_vif {int type; scalar_t__ addr; int /*<<< orphan*/  drv_priv; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/ * MAC; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  NL80211_IFTYPE_ADHOC 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  RTL818X_EEPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  RTL818X_EEPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8187_beacon_work ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8187_add_interface(struct ieee80211_hw *dev,
				 struct ieee80211_vif *vif)
{
	struct rtl8187_priv *priv = dev->priv;
	struct rtl8187_vif *vif_priv;
	int i;
	int ret = -EOPNOTSUPP;

	mutex_lock(&priv->conf_mutex);
	if (priv->vif)
		goto exit;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
		break;
	default:
		goto exit;
	}

	ret = 0;
	priv->vif = vif;

	/* Initialize driver private area */
	vif_priv = (struct rtl8187_vif *)&vif->drv_priv;
	vif_priv->dev = dev;
	INIT_DELAYED_WORK(&vif_priv->beacon_work, rtl8187_beacon_work);
	vif_priv->enable_beacon = false;


	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	for (i = 0; i < ETH_ALEN; i++)
		rtl818x_iowrite8(priv, &priv->map->MAC[i],
				 ((u8 *)vif->addr)[i]);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

exit:
	mutex_unlock(&priv->conf_mutex);
	return ret;
}