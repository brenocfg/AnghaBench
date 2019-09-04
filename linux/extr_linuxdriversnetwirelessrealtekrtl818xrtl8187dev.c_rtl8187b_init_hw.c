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
struct rtl8187_priv {int slot_time; int* aifsn; TYPE_2__* map; TYPE_1__* rf; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int CW_CONF; int EEPROM_CMD; int CONFIG1; int WPA_CONF; int CMD; int ACM_CONTROL; int MSR; int /*<<< orphan*/  HSSI_PARA; int /*<<< orphan*/  INT_MASK; int /*<<< orphan*/  RFPinsEnable; int /*<<< orphan*/  RFPinsSelect; int /*<<< orphan*/  RFPinsOutput; int /*<<< orphan*/  RF_TIMING; int /*<<< orphan*/  INT_MIG; int /*<<< orphan*/  TID_AC_MAP; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int RTL818X_CMD_RX_ENABLE ; 
 int RTL818X_CMD_TX_ENABLE ; 
 int RTL818X_CW_CONF_PERPACKET_RETRY ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int RTL818X_MSR_ENEDCA ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtl8187_cmd_reset (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8187_set_anaparam (struct rtl8187_priv*,int) ; 
 int** rtl8187b_reg_table ; 
 int rtl818x_ioread8 (struct rtl8187_priv*,int*) ; 
 int /*<<< orphan*/  rtl818x_iowrite16 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite16_idx (struct rtl8187_priv*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite32_idx (struct rtl8187_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int*,int) ; 
 int /*<<< orphan*/  rtl818x_iowrite8_idx (struct rtl8187_priv*,int*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 

__attribute__((used)) static int rtl8187b_init_hw(struct ieee80211_hw *dev)
{
	struct rtl8187_priv *priv = dev->priv;
	int res, i;
	u8 reg;

	rtl8187_set_anaparam(priv, true);

	/* Reset PLL sequence on 8187B. Realtek note: reduces power
	 * consumption about 30 mA */
	rtl818x_iowrite8(priv, (u8 *)0xFF61, 0x10);
	reg = rtl818x_ioread8(priv, (u8 *)0xFF62);
	rtl818x_iowrite8(priv, (u8 *)0xFF62, reg & ~(1 << 5));
	rtl818x_iowrite8(priv, (u8 *)0xFF62, reg | (1 << 5));

	res = rtl8187_cmd_reset(dev);
	if (res)
		return res;

	rtl8187_set_anaparam(priv, true);

	/* BRSR (Basic Rate Set Register) on 8187B looks to be the same as
	 * RESP_RATE on 8187L in Realtek sources: each bit should be each
	 * one of the 12 rates, all are enabled */
	rtl818x_iowrite16(priv, (__le16 *)0xFF34, 0x0FFF);

	reg = rtl818x_ioread8(priv, &priv->map->CW_CONF);
	reg |= RTL818X_CW_CONF_PERPACKET_RETRY;
	rtl818x_iowrite8(priv, &priv->map->CW_CONF, reg);

	/* Auto Rate Fallback Register (ARFR): 1M-54M setting */
	rtl818x_iowrite16_idx(priv, (__le16 *)0xFFE0, 0x0FFF, 1);
	rtl818x_iowrite8_idx(priv, (u8 *)0xFFE2, 0x00, 1);

	rtl818x_iowrite16_idx(priv, (__le16 *)0xFFD4, 0xFFFF, 1);

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);
	reg = rtl818x_ioread8(priv, &priv->map->CONFIG1);
	rtl818x_iowrite8(priv, &priv->map->CONFIG1, (reg & 0x3F) | 0x80);
	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);

	rtl818x_iowrite8(priv, &priv->map->WPA_CONF, 0);
	for (i = 0; i < ARRAY_SIZE(rtl8187b_reg_table); i++) {
		rtl818x_iowrite8_idx(priv,
				     (u8 *)(uintptr_t)
				     (rtl8187b_reg_table[i][0] | 0xFF00),
				     rtl8187b_reg_table[i][1],
				     rtl8187b_reg_table[i][2]);
	}

	rtl818x_iowrite16(priv, &priv->map->TID_AC_MAP, 0xFA50);
	rtl818x_iowrite16(priv, &priv->map->INT_MIG, 0);

	rtl818x_iowrite32_idx(priv, (__le32 *)0xFFF0, 0, 1);
	rtl818x_iowrite32_idx(priv, (__le32 *)0xFFF4, 0, 1);
	rtl818x_iowrite8_idx(priv, (u8 *)0xFFF8, 0, 1);

	rtl818x_iowrite32(priv, &priv->map->RF_TIMING, 0x00004001);

	/* RFSW_CTRL register */
	rtl818x_iowrite16_idx(priv, (__le16 *)0xFF72, 0x569A, 2);

	rtl818x_iowrite16(priv, &priv->map->RFPinsOutput, 0x0480);
	rtl818x_iowrite16(priv, &priv->map->RFPinsSelect, 0x2488);
	rtl818x_iowrite16(priv, &priv->map->RFPinsEnable, 0x1FFF);
	msleep(100);

	priv->rf->init(dev);

	reg = RTL818X_CMD_TX_ENABLE | RTL818X_CMD_RX_ENABLE;
	rtl818x_iowrite8(priv, &priv->map->CMD, reg);
	rtl818x_iowrite16(priv, &priv->map->INT_MASK, 0xFFFF);

	rtl818x_iowrite8(priv, (u8 *)0xFE41, 0xF4);
	rtl818x_iowrite8(priv, (u8 *)0xFE40, 0x00);
	rtl818x_iowrite8(priv, (u8 *)0xFE42, 0x00);
	rtl818x_iowrite8(priv, (u8 *)0xFE42, 0x01);
	rtl818x_iowrite8(priv, (u8 *)0xFE40, 0x0F);
	rtl818x_iowrite8(priv, (u8 *)0xFE42, 0x00);
	rtl818x_iowrite8(priv, (u8 *)0xFE42, 0x01);

	reg = rtl818x_ioread8(priv, (u8 *)0xFFDB);
	rtl818x_iowrite8(priv, (u8 *)0xFFDB, reg | (1 << 2));
	rtl818x_iowrite16_idx(priv, (__le16 *)0xFF72, 0x59FA, 3);
	rtl818x_iowrite16_idx(priv, (__le16 *)0xFF74, 0x59D2, 3);
	rtl818x_iowrite16_idx(priv, (__le16 *)0xFF76, 0x59D2, 3);
	rtl818x_iowrite16_idx(priv, (__le16 *)0xFF78, 0x19FA, 3);
	rtl818x_iowrite16_idx(priv, (__le16 *)0xFF7A, 0x19FA, 3);
	rtl818x_iowrite16_idx(priv, (__le16 *)0xFF7C, 0x00D0, 3);
	rtl818x_iowrite8(priv, (u8 *)0xFF61, 0);
	rtl818x_iowrite8_idx(priv, (u8 *)0xFF80, 0x0F, 1);
	rtl818x_iowrite8_idx(priv, (u8 *)0xFF83, 0x03, 1);
	rtl818x_iowrite8(priv, (u8 *)0xFFDA, 0x10);
	rtl818x_iowrite8_idx(priv, (u8 *)0xFF4D, 0x08, 2);

	rtl818x_iowrite32(priv, &priv->map->HSSI_PARA, 0x0600321B);

	rtl818x_iowrite16_idx(priv, (__le16 *)0xFFEC, 0x0800, 1);

	priv->slot_time = 0x9;
	priv->aifsn[0] = 2; /* AIFSN[AC_VO] */
	priv->aifsn[1] = 2; /* AIFSN[AC_VI] */
	priv->aifsn[2] = 7; /* AIFSN[AC_BK] */
	priv->aifsn[3] = 3; /* AIFSN[AC_BE] */
	rtl818x_iowrite8(priv, &priv->map->ACM_CONTROL, 0);

	/* ENEDCA flag must always be set, transmit issues? */
	rtl818x_iowrite8(priv, &priv->map->MSR, RTL818X_MSR_ENEDCA);

	return 0;
}