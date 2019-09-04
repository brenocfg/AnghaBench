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
typedef  int u8 ;
struct rtl8180_priv {TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  CONFIG3; int /*<<< orphan*/  ANAPARAM; int /*<<< orphan*/  ANAPARAM2; } ;

/* Variables and functions */
 int RTL818X_CONFIG3_ANAPARAM_WRITE ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  RTL8225_ANAPARAM2_OFF ; 
 int /*<<< orphan*/  RTL8225_ANAPARAM_OFF ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8180_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl8225_write (struct ieee80211_hw*,int,int) ; 

__attribute__((used)) static void rtl8225_rf_stop(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;
	u8 reg;

	rtl8225_write(dev, 0x4, 0x1f); msleep(1);

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG3);
	rtl818x_iowrite8(priv, &priv->map->CONFIG3, reg | RTL818X_CONFIG3_ANAPARAM_WRITE);
	rtl818x_iowrite32(priv, &priv->map->ANAPARAM2, RTL8225_ANAPARAM2_OFF);
	rtl818x_iowrite32(priv, &priv->map->ANAPARAM, RTL8225_ANAPARAM_OFF);
	rtl818x_iowrite8(priv, &priv->map->CONFIG3, reg & ~RTL818X_CONFIG3_ANAPARAM_WRITE);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);
}