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
typedef  int u32 ;
struct rtl8xxxu_priv {int* cck_tx_power_index_A; int* ht40_1s_tx_power_index_A; int tx_paths; int* cck_tx_power_index_B; int* ht40_1s_tx_power_index_B; TYPE_3__* ht20_tx_power_diff; TYPE_2__* ht40_tx_power_diff; TYPE_1__* ofdm_tx_power_diff; } ;
struct TYPE_6__ {scalar_t__ b; scalar_t__ a; } ;
struct TYPE_5__ {scalar_t__ b; scalar_t__ a; } ;
struct TYPE_4__ {scalar_t__ b; scalar_t__ a; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TX_AGC_A_CCK1_MCS32 ; 
 int /*<<< orphan*/  REG_TX_AGC_A_MCS03_MCS00 ; 
 int /*<<< orphan*/  REG_TX_AGC_A_MCS07_MCS04 ; 
 int /*<<< orphan*/  REG_TX_AGC_A_MCS11_MCS08 ; 
 int /*<<< orphan*/  REG_TX_AGC_A_MCS15_MCS12 ; 
 int /*<<< orphan*/  REG_TX_AGC_A_RATE18_06 ; 
 int /*<<< orphan*/  REG_TX_AGC_A_RATE54_24 ; 
 int /*<<< orphan*/  REG_TX_AGC_B_CCK11_A_CCK2_11 ; 
 int /*<<< orphan*/  REG_TX_AGC_B_CCK1_55_MCS32 ; 
 int /*<<< orphan*/  REG_TX_AGC_B_MCS03_MCS00 ; 
 int /*<<< orphan*/  REG_TX_AGC_B_MCS07_MCS04 ; 
 int /*<<< orphan*/  REG_TX_AGC_B_MCS11_MCS08 ; 
 int /*<<< orphan*/  REG_TX_AGC_B_MCS15_MCS12 ; 
 int /*<<< orphan*/  REG_TX_AGC_B_RATE18_06 ; 
 int /*<<< orphan*/  REG_TX_AGC_B_RATE54_24 ; 
 int rtl8xxxu_gen2_channel_to_group (int) ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rtl8192e_set_tx_power(struct rtl8xxxu_priv *priv, int channel, bool ht40)
{
	u32 val32, ofdm, mcs;
	u8 cck, ofdmbase, mcsbase;
	int group, tx_idx;

	tx_idx = 0;
	group = rtl8xxxu_gen2_channel_to_group(channel);

	cck = priv->cck_tx_power_index_A[group];

	val32 = rtl8xxxu_read32(priv, REG_TX_AGC_A_CCK1_MCS32);
	val32 &= 0xffff00ff;
	val32 |= (cck << 8);
	rtl8xxxu_write32(priv, REG_TX_AGC_A_CCK1_MCS32, val32);

	val32 = rtl8xxxu_read32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11);
	val32 &= 0xff;
	val32 |= ((cck << 8) | (cck << 16) | (cck << 24));
	rtl8xxxu_write32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11, val32);

	ofdmbase = priv->ht40_1s_tx_power_index_A[group];
	ofdmbase += priv->ofdm_tx_power_diff[tx_idx].a;
	ofdm = ofdmbase | ofdmbase << 8 | ofdmbase << 16 | ofdmbase << 24;

	rtl8xxxu_write32(priv, REG_TX_AGC_A_RATE18_06, ofdm);
	rtl8xxxu_write32(priv, REG_TX_AGC_A_RATE54_24, ofdm);

	mcsbase = priv->ht40_1s_tx_power_index_A[group];
	if (ht40)
		mcsbase += priv->ht40_tx_power_diff[tx_idx++].a;
	else
		mcsbase += priv->ht20_tx_power_diff[tx_idx++].a;
	mcs = mcsbase | mcsbase << 8 | mcsbase << 16 | mcsbase << 24;

	rtl8xxxu_write32(priv, REG_TX_AGC_A_MCS03_MCS00, mcs);
	rtl8xxxu_write32(priv, REG_TX_AGC_A_MCS07_MCS04, mcs);
	rtl8xxxu_write32(priv, REG_TX_AGC_A_MCS11_MCS08, mcs);
	rtl8xxxu_write32(priv, REG_TX_AGC_A_MCS15_MCS12, mcs);

	if (priv->tx_paths > 1) {
		cck = priv->cck_tx_power_index_B[group];

		val32 = rtl8xxxu_read32(priv, REG_TX_AGC_B_CCK1_55_MCS32);
		val32 &= 0xff;
		val32 |= ((cck << 8) | (cck << 16) | (cck << 24));
		rtl8xxxu_write32(priv, REG_TX_AGC_B_CCK1_55_MCS32, val32);

		val32 = rtl8xxxu_read32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11);
		val32 &= 0xffffff00;
		val32 |= cck;
		rtl8xxxu_write32(priv, REG_TX_AGC_B_CCK11_A_CCK2_11, val32);

		ofdmbase = priv->ht40_1s_tx_power_index_B[group];
		ofdmbase += priv->ofdm_tx_power_diff[tx_idx].b;
		ofdm = ofdmbase | ofdmbase << 8 |
			ofdmbase << 16 | ofdmbase << 24;

		rtl8xxxu_write32(priv, REG_TX_AGC_B_RATE18_06, ofdm);
		rtl8xxxu_write32(priv, REG_TX_AGC_B_RATE54_24, ofdm);

		mcsbase = priv->ht40_1s_tx_power_index_B[group];
		if (ht40)
			mcsbase += priv->ht40_tx_power_diff[tx_idx++].b;
		else
			mcsbase += priv->ht20_tx_power_diff[tx_idx++].b;
		mcs = mcsbase | mcsbase << 8 | mcsbase << 16 | mcsbase << 24;

		rtl8xxxu_write32(priv, REG_TX_AGC_B_MCS03_MCS00, mcs);
		rtl8xxxu_write32(priv, REG_TX_AGC_B_MCS07_MCS04, mcs);
		rtl8xxxu_write32(priv, REG_TX_AGC_B_MCS11_MCS08, mcs);
		rtl8xxxu_write32(priv, REG_TX_AGC_B_MCS15_MCS12, mcs);
	}
}