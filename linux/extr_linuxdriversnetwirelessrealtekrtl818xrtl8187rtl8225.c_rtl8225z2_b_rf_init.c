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
struct rtl8187_priv {TYPE_1__* map; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  TX_ANTENNA; int /*<<< orphan*/  TX_GAIN_OFDM; int /*<<< orphan*/  TX_GAIN_CCK; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl8225_write (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8225_write_phy_cck (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8225_write_phy_ofdm (struct ieee80211_hw*,int,int) ; 
 int* rtl8225z2_agc ; 
 int* rtl8225z2_ofdm ; 
 int* rtl8225z2_rxgain ; 

__attribute__((used)) static void rtl8225z2_b_rf_init(struct ieee80211_hw *dev)
{
	struct rtl8187_priv *priv = dev->priv;
	int i;

	rtl8225_write(dev, 0x0, 0x0B7);
	rtl8225_write(dev, 0x1, 0xEE0);
	rtl8225_write(dev, 0x2, 0x44D);
	rtl8225_write(dev, 0x3, 0x441);
	rtl8225_write(dev, 0x4, 0x8C3);
	rtl8225_write(dev, 0x5, 0xC72);
	rtl8225_write(dev, 0x6, 0x0E6);
	rtl8225_write(dev, 0x7, 0x82A);
	rtl8225_write(dev, 0x8, 0x03F);
	rtl8225_write(dev, 0x9, 0x335);
	rtl8225_write(dev, 0xa, 0x9D4);
	rtl8225_write(dev, 0xb, 0x7BB);
	rtl8225_write(dev, 0xc, 0x850);
	rtl8225_write(dev, 0xd, 0xCDF);
	rtl8225_write(dev, 0xe, 0x02B);
	rtl8225_write(dev, 0xf, 0x114);

	rtl8225_write(dev, 0x0, 0x1B7);

	for (i = 0; i < ARRAY_SIZE(rtl8225z2_rxgain); i++) {
		rtl8225_write(dev, 0x1, i + 1);
		rtl8225_write(dev, 0x2, rtl8225z2_rxgain[i]);
	}

	rtl8225_write(dev, 0x3, 0x080);
	rtl8225_write(dev, 0x5, 0x004);
	rtl8225_write(dev, 0x0, 0x0B7);

	rtl8225_write(dev, 0x2, 0xC4D);

	rtl8225_write(dev, 0x2, 0x44D);
	rtl8225_write(dev, 0x0, 0x2BF);

	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_CCK, 0x03);
	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_OFDM, 0x07);
	rtl818x_iowrite8(priv, &priv->map->TX_ANTENNA, 0x03);

	rtl8225_write_phy_ofdm(dev, 0x80, 0x12);
	for (i = 0; i < ARRAY_SIZE(rtl8225z2_agc); i++) {
		rtl8225_write_phy_ofdm(dev, 0xF, rtl8225z2_agc[i]);
		rtl8225_write_phy_ofdm(dev, 0xE, 0x80 + i);
		rtl8225_write_phy_ofdm(dev, 0xE, 0);
	}
	rtl8225_write_phy_ofdm(dev, 0x80, 0x10);

	for (i = 0; i < ARRAY_SIZE(rtl8225z2_ofdm); i++)
		rtl8225_write_phy_ofdm(dev, i, rtl8225z2_ofdm[i]);

	rtl8225_write_phy_ofdm(dev, 0x97, 0x46);
	rtl8225_write_phy_ofdm(dev, 0xa4, 0xb6);
	rtl8225_write_phy_ofdm(dev, 0x85, 0xfc);
	rtl8225_write_phy_cck(dev, 0xc1, 0x88);
}