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
typedef  int u8 ;
struct rtl8187_priv {TYPE_2__* map; TYPE_1__* rf; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int GPIO0; int GP_ENABLE; int EEPROM_CMD; int CONFIG1; int WPA_CONF; int RATE_FALLBACK; int RESP_RATE; int CONFIG3; int PGSELECT; int TALLY_SEL; int /*<<< orphan*/  BRSR; int /*<<< orphan*/  RFPinsEnable; int /*<<< orphan*/  RF_PARA; int /*<<< orphan*/  RF_TIMING; int /*<<< orphan*/  RFPinsSelect; int /*<<< orphan*/  RFPinsOutput; int /*<<< orphan*/  INT_TIMEOUT; int /*<<< orphan*/  INT_MASK; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtl8187_cmd_reset (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8187_set_anaparam (struct rtl8187_priv*,int) ; 
 int rtl818x_ioread8 (struct rtl8187_priv*,int*) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int*,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 

__attribute__((used)) static int rtl8187_init_hw(struct ieee80211_hw *dev)
{
	struct rtl8187_priv *priv = dev->priv;
	u8 reg;
	int res;

	/* reset */
	rtl8187_set_anaparam(priv, true);

	rtl818x_iowrite16(priv, &priv->map->INT_MASK, 0);

	msleep(200);
	rtl818x_iowrite8(priv, (u8 *)0xFE18, 0x10);
	rtl818x_iowrite8(priv, (u8 *)0xFE18, 0x11);
	rtl818x_iowrite8(priv, (u8 *)0xFE18, 0x00);
	msleep(200);

	res = rtl8187_cmd_reset(dev);
	if (res)
		return res;

	rtl8187_set_anaparam(priv, true);

	/* setup card */
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, 0);
	rtl818x_iowrite8(priv, &priv->map->GPIO0, 0);

	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, (4 << 8));
	rtl818x_iowrite8(priv, &priv->map->GPIO0, 1);
	rtl818x_iowrite8(priv, &priv->map->GP_ENABLE, 0);

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_CONFIG);

	rtl818x_iowrite16(priv, (__le16 *)0xFFF4, 0xFFFF);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG1);
	reg &= 0x3F;
	reg |= 0x80;
	rtl818x_iowrite8(priv, &priv->map->CONFIG1, reg);

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD, RTL818X_EEPROM_CMD_NORMAL);

	rtl818x_iowrite32(priv, &priv->map->INT_TIMEOUT, 0);
	rtl818x_iowrite8(priv, &priv->map->WPA_CONF, 0);
	rtl818x_iowrite8(priv, &priv->map->RATE_FALLBACK, 0);

	// TODO: set RESP_RATE and BRSR properly
	rtl818x_iowrite8(priv, &priv->map->RESP_RATE, (8 << 4) | 0);
	rtl818x_iowrite16(priv, &priv->map->BRSR, 0x01F3);

	/* host_usb_init */
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, 0);
	rtl818x_iowrite8(priv, &priv->map->GPIO0, 0);
	reg = rtl818x_ioread8(priv, (u8 *)0xFE53);
	rtl818x_iowrite8(priv, (u8 *)0xFE53, reg | (1 << 7));
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, (4 << 8));
	rtl818x_iowrite8(priv, &priv->map->GPIO0, 0x20);
	rtl818x_iowrite8(priv, &priv->map->GP_ENABLE, 0);
	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, 0x80);
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, 0x80);
	rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, 0x80);
	msleep(100);

	rtl818x_iowrite32(priv, &priv->map->RF_TIMING, 0x000a8008);
	rtl818x_iowrite16(priv, &priv->map->BRSR, 0xFFFF);
	rtl818x_iowrite32(priv, &priv->map->RF_PARA, 0x00100044);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);
	rtl818x_iowrite8(priv, &priv->map->CONFIG3, 0x44);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);
	rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, 0x1FF7);
	msleep(100);

	priv->rf->init(dev);

	rtl818x_iowrite16(priv, &priv->map->BRSR, 0x01F3);
	reg = rtl818x_ioread8(priv, &priv->map->PGSELECT) & ~1;
	rtl818x_iowrite8(priv, &priv->map->PGSELECT, reg | 1);
	rtl818x_iowrite16(priv, (__le16 *)0xFFFE, 0x10);
	rtl818x_iowrite8(priv, &priv->map->TALLY_SEL, 0x80);
	rtl818x_iowrite8(priv, (u8 *)0xFFFF, 0x60);
	rtl818x_iowrite8(priv, &priv->map->PGSELECT, reg);

	return 0;
}