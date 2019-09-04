#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_PROT_CFG ; 
 int /*<<< orphan*/  CCK_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  GF20_PROT_CFG ; 
 int /*<<< orphan*/  GF20_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  GF40_PROT_CFG ; 
 int /*<<< orphan*/  GF40_PROT_CFG_RTS_TH_EN ; 
 scalar_t__ IEEE80211_MAX_RTS_THRESHOLD ; 
 int /*<<< orphan*/  MM20_PROT_CFG ; 
 int /*<<< orphan*/  MM20_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  MM40_PROT_CFG ; 
 int /*<<< orphan*/  MM40_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  OFDM_PROT_CFG ; 
 int /*<<< orphan*/  OFDM_PROT_CFG_RTS_TH_EN ; 
 int /*<<< orphan*/  TX_RTS_CFG ; 
 int /*<<< orphan*/  TX_RTS_CFG_RTS_THRES ; 
 scalar_t__ rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (scalar_t__*,int /*<<< orphan*/ ,int) ; 

int rt2800_set_rts_threshold(struct ieee80211_hw *hw, u32 value)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	u32 reg;
	bool enabled = (value < IEEE80211_MAX_RTS_THRESHOLD);

	reg = rt2800_register_read(rt2x00dev, TX_RTS_CFG);
	rt2x00_set_field32(&reg, TX_RTS_CFG_RTS_THRES, value);
	rt2800_register_write(rt2x00dev, TX_RTS_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, CCK_PROT_CFG);
	rt2x00_set_field32(&reg, CCK_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_register_write(rt2x00dev, CCK_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, OFDM_PROT_CFG);
	rt2x00_set_field32(&reg, OFDM_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_register_write(rt2x00dev, OFDM_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, MM20_PROT_CFG);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_register_write(rt2x00dev, MM20_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, MM40_PROT_CFG);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_register_write(rt2x00dev, MM40_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, GF20_PROT_CFG);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_register_write(rt2x00dev, GF20_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, GF40_PROT_CFG);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_RTS_TH_EN, enabled);
	rt2800_register_write(rt2x00dev, GF40_PROT_CFG, reg);

	return 0;
}