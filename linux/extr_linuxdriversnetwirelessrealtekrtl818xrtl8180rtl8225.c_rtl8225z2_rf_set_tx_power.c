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
struct rtl8180_priv {TYPE_2__* map; TYPE_1__* channels; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  TX_GAIN_OFDM; int /*<<< orphan*/  TX_GAIN_CCK; } ;
struct TYPE_3__ {int hw_value; } ;

/* Variables and functions */
 int min (int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl8225_write_phy_cck (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8225_write_phy_ofdm (struct ieee80211_hw*,int,int) ; 
 int* rtl8225z2_tx_power_cck ; 
 int* rtl8225z2_tx_power_cck_A ; 
 int* rtl8225z2_tx_power_cck_B ; 
 int* rtl8225z2_tx_power_cck_ch14 ; 

__attribute__((used)) static void rtl8225z2_rf_set_tx_power(struct ieee80211_hw *dev, int channel)
{
	struct rtl8180_priv *priv = dev->priv;
	u8 cck_power, ofdm_power;
	const u8 *tmp;
	int i;

	cck_power = priv->channels[channel - 1].hw_value & 0xFF;
	ofdm_power = priv->channels[channel - 1].hw_value >> 8;

	if (channel == 14)
		tmp = rtl8225z2_tx_power_cck_ch14;
	else if (cck_power == 12)
		tmp = rtl8225z2_tx_power_cck_B;
	else if (cck_power == 13)
		tmp = rtl8225z2_tx_power_cck_A;
	else
		tmp = rtl8225z2_tx_power_cck;

	for (i = 0; i < 8; i++)
		rtl8225_write_phy_cck(dev, 0x44 + i, *tmp++);

	cck_power = min(cck_power, (u8)35);
	if (cck_power == 13 || cck_power == 14)
		cck_power = 12;
	if (cck_power >= 15)
		cck_power -= 2;

	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_CCK, cck_power);
	rtl818x_ioread8(priv, &priv->map->TX_GAIN_CCK);
	msleep(1);

	ofdm_power = min(ofdm_power, (u8)35);
	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_OFDM, ofdm_power);

	rtl8225_write_phy_ofdm(dev, 2, 0x62);
	rtl8225_write_phy_ofdm(dev, 5, 0x00);
	rtl8225_write_phy_ofdm(dev, 6, 0x40);
	rtl8225_write_phy_ofdm(dev, 7, 0x00);
	rtl8225_write_phy_ofdm(dev, 8, 0x40);

	msleep(1);
}