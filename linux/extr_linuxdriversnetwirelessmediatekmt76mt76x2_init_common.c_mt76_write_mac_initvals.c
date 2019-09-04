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
typedef  struct mt76x2_reg_pair {int member_0; int member_1; } const mt76x2_reg_pair ;
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct mt76x2_reg_pair const*) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
#define  MT_AMPDU_MAX_LEN_20M1S 178 
#define  MT_AMPDU_MAX_LEN_20M2S 177 
#define  MT_AUX_CLK_CFG 176 
#define  MT_BKOFF_SLOT_CFG 175 
 int MT_CCK_PROT_CFG ; 
#define  MT_DACCLK_EN_DLY_CFG 174 
#define  MT_EFUSE_CTRL 173 
#define  MT_EXP_ACK_TIME 172 
#define  MT_FCE_PSE_CTRL 171 
#define  MT_FCE_WLAN_FLOW_CONTROL1 170 
 int MT_GF20_PROT_CFG ; 
 int MT_GF40_PROT_CFG ; 
#define  MT_HEADER_TRANS_CTRL_REG 169 
#define  MT_HT_BASIC_RATE 168 
#define  MT_HT_CTRL_CFG 167 
#define  MT_HT_FBK_TO_LEGACY 166 
#define  MT_LEGACY_BASIC_RATE 165 
#define  MT_MAC_SYS_CTRL 164 
#define  MT_MAX_LEN_CFG 163 
 int MT_MM20_PROT_CFG ; 
 int MT_MM40_PROT_CFG ; 
 int MT_OFDM_PROT_CFG ; 
#define  MT_PAUSE_ENABLE_CONTROL1 162 
#define  MT_PBF_CFG 161 
#define  MT_PBF_SYS_CTRL 160 
#define  MT_PIFS_TX_CFG 159 
#define  MT_PN_PAD_MODE 158 
#define  MT_PROT_AUTO_TX_CFG 157 
 int /*<<< orphan*/  MT_PROT_CFG_CTRL ; 
 int /*<<< orphan*/  MT_PROT_CFG_NAV ; 
 int /*<<< orphan*/  MT_PROT_CFG_RATE ; 
 int MT_PROT_CFG_RTS_THRESH ; 
 int /*<<< orphan*/  MT_PROT_CFG_TXOP_ALLOW ; 
#define  MT_PWR_PIN_CFG 156 
#define  MT_RX_FILTR_CFG 155 
#define  MT_TBTT_SYNC_CFG 154 
#define  MT_TSO_CTRL 153 
#define  MT_TXOP_CTRL_CFG 152 
#define  MT_TXOP_HLDR_ET 151 
#define  MT_TX_ALC_CFG_4 150 
#define  MT_TX_ALC_VGA3 149 
#define  MT_TX_PROT_CFG6 148 
#define  MT_TX_PROT_CFG7 147 
#define  MT_TX_PROT_CFG8 146 
#define  MT_TX_PWR_CFG_0 145 
#define  MT_TX_PWR_CFG_1 144 
#define  MT_TX_PWR_CFG_2 143 
#define  MT_TX_PWR_CFG_3 142 
#define  MT_TX_PWR_CFG_4 141 
#define  MT_TX_PWR_CFG_7 140 
#define  MT_TX_PWR_CFG_8 139 
#define  MT_TX_PWR_CFG_9 138 
#define  MT_TX_RETRY_CFG 137 
#define  MT_TX_RTS_CFG 136 
#define  MT_TX_SW_CFG0 135 
#define  MT_TX_SW_CFG1 134 
#define  MT_TX_SW_CFG2 133 
#define  MT_TX_SW_CFG3 132 
#define  MT_TX_TIMEOUT_CFG 131 
#define  MT_VHT_HT_FBK_CFG1 130 
#define  MT_WPDMA_DELAY_INT_CFG 129 
#define  MT_XIFS_TIME_CFG 128 
 int /*<<< orphan*/  mt76x2_write_reg_pairs (struct mt76x2_dev*,struct mt76x2_reg_pair const*,int /*<<< orphan*/ ) ; 

void mt76_write_mac_initvals(struct mt76x2_dev *dev)
{
#define DEFAULT_PROT_CFG_CCK				\
	(FIELD_PREP(MT_PROT_CFG_RATE, 0x3) |		\
	 FIELD_PREP(MT_PROT_CFG_NAV, 1) |		\
	 FIELD_PREP(MT_PROT_CFG_TXOP_ALLOW, 0x3f) |	\
	 MT_PROT_CFG_RTS_THRESH)

#define DEFAULT_PROT_CFG_OFDM				\
	(FIELD_PREP(MT_PROT_CFG_RATE, 0x2004) |		\
	 FIELD_PREP(MT_PROT_CFG_NAV, 1) |			\
	 FIELD_PREP(MT_PROT_CFG_TXOP_ALLOW, 0x3f) |	\
	 MT_PROT_CFG_RTS_THRESH)

#define DEFAULT_PROT_CFG_20				\
	(FIELD_PREP(MT_PROT_CFG_RATE, 0x2004) |		\
	 FIELD_PREP(MT_PROT_CFG_CTRL, 1) |		\
	 FIELD_PREP(MT_PROT_CFG_NAV, 1) |			\
	 FIELD_PREP(MT_PROT_CFG_TXOP_ALLOW, 0x17))

#define DEFAULT_PROT_CFG_40				\
	(FIELD_PREP(MT_PROT_CFG_RATE, 0x2084) |		\
	 FIELD_PREP(MT_PROT_CFG_CTRL, 1) |		\
	 FIELD_PREP(MT_PROT_CFG_NAV, 1) |			\
	 FIELD_PREP(MT_PROT_CFG_TXOP_ALLOW, 0x3f))

	static const struct mt76x2_reg_pair vals[] = {
		/* Copied from MediaTek reference source */
		{ MT_PBF_SYS_CTRL,		0x00080c00 },
		{ MT_PBF_CFG,			0x1efebcff },
		{ MT_FCE_PSE_CTRL,		0x00000001 },
		{ MT_MAC_SYS_CTRL,		0x0000000c },
		{ MT_MAX_LEN_CFG,		0x003e3f00 },
		{ MT_AMPDU_MAX_LEN_20M1S,	0xaaa99887 },
		{ MT_AMPDU_MAX_LEN_20M2S,	0x000000aa },
		{ MT_XIFS_TIME_CFG,		0x33a40d0a },
		{ MT_BKOFF_SLOT_CFG,		0x00000209 },
		{ MT_TBTT_SYNC_CFG,		0x00422010 },
		{ MT_PWR_PIN_CFG,		0x00000000 },
		{ 0x1238,			0x001700c8 },
		{ MT_TX_SW_CFG0,		0x00101001 },
		{ MT_TX_SW_CFG1,		0x00010000 },
		{ MT_TX_SW_CFG2,		0x00000000 },
		{ MT_TXOP_CTRL_CFG,		0x0400583f },
		{ MT_TX_RTS_CFG,		0x00100020 },
		{ MT_TX_TIMEOUT_CFG,		0x000a2290 },
		{ MT_TX_RETRY_CFG,		0x47f01f0f },
		{ MT_EXP_ACK_TIME,		0x002c00dc },
		{ MT_TX_PROT_CFG6,		0xe3f42004 },
		{ MT_TX_PROT_CFG7,		0xe3f42084 },
		{ MT_TX_PROT_CFG8,		0xe3f42104 },
		{ MT_PIFS_TX_CFG,		0x00060fff },
		{ MT_RX_FILTR_CFG,		0x00015f97 },
		{ MT_LEGACY_BASIC_RATE,		0x0000017f },
		{ MT_HT_BASIC_RATE,		0x00004003 },
		{ MT_PN_PAD_MODE,		0x00000003 },
		{ MT_TXOP_HLDR_ET,		0x00000002 },
		{ 0xa44,			0x00000000 },
		{ MT_HEADER_TRANS_CTRL_REG,	0x00000000 },
		{ MT_TSO_CTRL,			0x00000000 },
		{ MT_AUX_CLK_CFG,		0x00000000 },
		{ MT_DACCLK_EN_DLY_CFG,		0x00000000 },
		{ MT_TX_ALC_CFG_4,		0x00000000 },
		{ MT_TX_ALC_VGA3,		0x00000000 },
		{ MT_TX_PWR_CFG_0,		0x3a3a3a3a },
		{ MT_TX_PWR_CFG_1,		0x3a3a3a3a },
		{ MT_TX_PWR_CFG_2,		0x3a3a3a3a },
		{ MT_TX_PWR_CFG_3,		0x3a3a3a3a },
		{ MT_TX_PWR_CFG_4,		0x3a3a3a3a },
		{ MT_TX_PWR_CFG_7,		0x3a3a3a3a },
		{ MT_TX_PWR_CFG_8,		0x0000003a },
		{ MT_TX_PWR_CFG_9,		0x0000003a },
		{ MT_EFUSE_CTRL,		0x0000d000 },
		{ MT_PAUSE_ENABLE_CONTROL1,	0x0000000a },
		{ MT_FCE_WLAN_FLOW_CONTROL1,	0x60401c18 },
		{ MT_WPDMA_DELAY_INT_CFG,	0x94ff0000 },
		{ MT_TX_SW_CFG3,		0x00000004 },
		{ MT_HT_FBK_TO_LEGACY,		0x00001818 },
		{ MT_VHT_HT_FBK_CFG1,		0xedcba980 },
		{ MT_PROT_AUTO_TX_CFG,		0x00830083 },
		{ MT_HT_CTRL_CFG,		0x000001ff },
	};
	struct mt76x2_reg_pair prot_vals[] = {
		{ MT_CCK_PROT_CFG,		DEFAULT_PROT_CFG_CCK },
		{ MT_OFDM_PROT_CFG,		DEFAULT_PROT_CFG_OFDM },
		{ MT_MM20_PROT_CFG,		DEFAULT_PROT_CFG_20 },
		{ MT_MM40_PROT_CFG,		DEFAULT_PROT_CFG_40 },
		{ MT_GF20_PROT_CFG,		DEFAULT_PROT_CFG_20 },
		{ MT_GF40_PROT_CFG,		DEFAULT_PROT_CFG_40 },
	};

	mt76x2_write_reg_pairs(dev, vals, ARRAY_SIZE(vals));
	mt76x2_write_reg_pairs(dev, prot_vals, ARRAY_SIZE(prot_vals));
}