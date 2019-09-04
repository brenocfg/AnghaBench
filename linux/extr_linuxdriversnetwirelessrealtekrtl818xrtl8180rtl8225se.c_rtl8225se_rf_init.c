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
typedef  int u32 ;
struct rtl8180_priv {int xtal_in; int xtal_out; TYPE_1__* map; scalar_t__ xtal_cal; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rtl8180_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  TX_ANTENNA; int /*<<< orphan*/  TX_GAIN_OFDM; int /*<<< orphan*/  TX_GAIN_CCK; } ;

/* Variables and functions */
 int /*<<< orphan*/ * REG_ADDR1 (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtl8187se_rf_readreg (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8187se_rf_writereg (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8187se_write_initial_gain (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl8187se_write_ofdm_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl8187se_write_rf_gain (struct ieee80211_hw*) ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl8225se_write_phy_cck (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8225se_write_phy_ofdm (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  rtl8225se_write_zebra_agc (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*,...) ; 

void rtl8225se_rf_init(struct ieee80211_hw *dev)
{
	struct rtl8180_priv *priv = dev->priv;
	u32 rf23, rf24;
	u8 d_cut = 0;
	u8 tmp;

	/* Page 1 */
	rtl8187se_rf_writereg(dev, 0x00, 0x013F); mdelay(1);
	rf23 = rtl8187se_rf_readreg(dev, 0x08); mdelay(1);
	rf24 = rtl8187se_rf_readreg(dev, 0x09); mdelay(1);
	if (rf23 == 0x0818 && rf24 == 0x070C)
		d_cut = 1;

	wiphy_info(dev->wiphy, "RTL8225-SE version %s\n",
		d_cut ? "D" : "not-D");

	/* Page 0: reg 0 - 15 */
	rtl8187se_rf_writereg(dev, 0x00, 0x009F); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x01, 0x06E0); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x02, 0x004D); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x03, 0x07F1); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x04, 0x0975); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x05, 0x0C72); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x06, 0x0AE6); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x07, 0x00CA); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x08, 0x0E1C); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x09, 0x02F0); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0A, 0x09D0); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0B, 0x01BA); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0C, 0x0640); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0D, 0x08DF); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0E, 0x0020); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0F, 0x0990); mdelay(1);
	/* page 1: reg 16-30 */
	rtl8187se_rf_writereg(dev, 0x00, 0x013F); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x03, 0x0806); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x04, 0x03A7); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x05, 0x059B); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x06, 0x0081); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x07, 0x01A0); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0A, 0x0001); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0B, 0x0418); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0C, 0x0FBE); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0D, 0x0008); mdelay(1);
	if (d_cut)
		rtl8187se_rf_writereg(dev, 0x0E, 0x0807);
	else
		rtl8187se_rf_writereg(dev, 0x0E, 0x0806);
	mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0F, 0x0ACC); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x00, 0x01D7); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x03, 0x0E00); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x04, 0x0E50); mdelay(1);

	rtl8187se_write_rf_gain(dev);

	rtl8187se_rf_writereg(dev, 0x05, 0x0203); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x06, 0x0200); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x00, 0x0137); mdelay(11);
	rtl8187se_rf_writereg(dev, 0x0D, 0x0008); mdelay(11);
	rtl8187se_rf_writereg(dev, 0x00, 0x0037); mdelay(11);
	rtl8187se_rf_writereg(dev, 0x04, 0x0160); mdelay(11);
	rtl8187se_rf_writereg(dev, 0x07, 0x0080); mdelay(11);
	rtl8187se_rf_writereg(dev, 0x02, 0x088D); msleep(221);
	rtl8187se_rf_writereg(dev, 0x00, 0x0137); mdelay(11);
	rtl8187se_rf_writereg(dev, 0x07, 0x0000); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x07, 0x0180); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x07, 0x0220); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x07, 0x03E0); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x06, 0x00C1); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0A, 0x0001); mdelay(1);
	if (priv->xtal_cal) {
		tmp = (priv->xtal_in << 4) | (priv->xtal_out << 1) |
		      (1 << 11) | (1 << 9);
		rtl8187se_rf_writereg(dev, 0x0F, tmp);
		wiphy_info(dev->wiphy, "Xtal cal\n");
		mdelay(1);
	} else {
		wiphy_info(dev->wiphy, "NO Xtal cal\n");
		rtl8187se_rf_writereg(dev, 0x0F, 0x0ACC);
		mdelay(1);
	}
	/* page 0 */
	rtl8187se_rf_writereg(dev, 0x00, 0x00BF); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x0D, 0x08DF); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x02, 0x004D); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x04, 0x0975); msleep(31);
	rtl8187se_rf_writereg(dev, 0x00, 0x0197); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x05, 0x05AB); mdelay(1);

	rtl8187se_rf_writereg(dev, 0x00, 0x009F); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x01, 0x0000); mdelay(1);
	rtl8187se_rf_writereg(dev, 0x02, 0x0000); mdelay(1);
	/* power save parameters */
	/* TODO: move to dev.c */
	rtl818x_iowrite8(priv, REG_ADDR1(0x024E),
		 rtl818x_ioread8(priv, REG_ADDR1(0x24E)) & 0x9F);
	rtl8225se_write_phy_cck(dev, 0x00, 0xC8);
	rtl8225se_write_phy_cck(dev, 0x06, 0x1C);
	rtl8225se_write_phy_cck(dev, 0x10, 0x78);
	rtl8225se_write_phy_cck(dev, 0x2E, 0xD0);
	rtl8225se_write_phy_cck(dev, 0x2F, 0x06);
	rtl8225se_write_phy_cck(dev, 0x01, 0x46);

	/* power control */
	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_CCK, 0x10);
	rtl818x_iowrite8(priv, &priv->map->TX_GAIN_OFDM, 0x1B);

	rtl818x_iowrite8(priv, &priv->map->TX_ANTENNA, 0x03);
	rtl8225se_write_phy_ofdm(dev, 0x00, 0x12);

	rtl8225se_write_zebra_agc(dev);

	rtl8225se_write_phy_ofdm(dev, 0x10, 0x00);

	rtl8187se_write_ofdm_config(dev);

	/* turn on RF */
	rtl8187se_rf_writereg(dev, 0x00, 0x009F); udelay(500);
	rtl8187se_rf_writereg(dev, 0x04, 0x0972); udelay(500);
	/* turn on RF again */
	rtl8187se_rf_writereg(dev, 0x00, 0x009F); udelay(500);
	rtl8187se_rf_writereg(dev, 0x04, 0x0972); udelay(500);
	/* turn on BB */
	rtl8225se_write_phy_ofdm(dev, 0x10, 0x40);
	rtl8225se_write_phy_ofdm(dev, 0x12, 0x40);

	rtl8187se_write_initial_gain(dev, 4);
}