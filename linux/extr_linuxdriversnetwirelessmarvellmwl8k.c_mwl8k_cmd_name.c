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
typedef  int u16 ;
typedef  int __le16 ;

/* Variables and functions */
#define  MWL8K_CMD_BASTREAM 158 
#define  MWL8K_CMD_BSS_START 157 
#define  MWL8K_CMD_CODE_DNLD 156 
#define  MWL8K_CMD_ENABLE_SNIFFER 155 
#define  MWL8K_CMD_GET_HW_SPEC 154 
#define  MWL8K_CMD_GET_STAT 153 
#define  MWL8K_CMD_GET_WATCHDOG_BITMAP 152 
#define  MWL8K_CMD_MAC_MULTICAST_ADR 151 
#define  MWL8K_CMD_MIMO_CONFIG 150 
#define  MWL8K_CMD_RADIO_CONTROL 149 
#define  MWL8K_CMD_RF_ANTENNA 148 
#define  MWL8K_CMD_RF_TX_POWER 147 
#define  MWL8K_CMD_RTS_THRESHOLD 146 
#define  MWL8K_CMD_SET_AID 145 
#define  MWL8K_CMD_SET_BEACON 144 
#define  MWL8K_CMD_SET_EDCA_PARAMS 143 
#define  MWL8K_CMD_SET_FINALIZE_JOIN 142 
#define  MWL8K_CMD_SET_HW_SPEC 141 
#define  MWL8K_CMD_SET_MAC_ADDR 140 
#define  MWL8K_CMD_SET_NEW_STN 139 
#define  MWL8K_CMD_SET_POST_SCAN 138 
#define  MWL8K_CMD_SET_PRE_SCAN 137 
#define  MWL8K_CMD_SET_RATE 136 
#define  MWL8K_CMD_SET_RATEADAPT_MODE 135 
#define  MWL8K_CMD_SET_RF_CHANNEL 134 
#define  MWL8K_CMD_SET_SLOT 133 
#define  MWL8K_CMD_SET_WMM_MODE 132 
#define  MWL8K_CMD_TX_POWER 131 
#define  MWL8K_CMD_UPDATE_ENCRYPTION 130 
#define  MWL8K_CMD_UPDATE_STADB 129 
#define  MWL8K_CMD_USE_FIXED_RATE 128 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static const char *mwl8k_cmd_name(__le16 cmd, char *buf, int bufsize)
{
	u16 command = le16_to_cpu(cmd);

#define MWL8K_CMDNAME(x)	case MWL8K_CMD_##x: do {\
					snprintf(buf, bufsize, "%s", #x);\
					return buf;\
					} while (0)
	switch (command & ~0x8000) {
		MWL8K_CMDNAME(CODE_DNLD);
		MWL8K_CMDNAME(GET_HW_SPEC);
		MWL8K_CMDNAME(SET_HW_SPEC);
		MWL8K_CMDNAME(MAC_MULTICAST_ADR);
		MWL8K_CMDNAME(GET_STAT);
		MWL8K_CMDNAME(RADIO_CONTROL);
		MWL8K_CMDNAME(RF_TX_POWER);
		MWL8K_CMDNAME(TX_POWER);
		MWL8K_CMDNAME(RF_ANTENNA);
		MWL8K_CMDNAME(SET_BEACON);
		MWL8K_CMDNAME(SET_PRE_SCAN);
		MWL8K_CMDNAME(SET_POST_SCAN);
		MWL8K_CMDNAME(SET_RF_CHANNEL);
		MWL8K_CMDNAME(SET_AID);
		MWL8K_CMDNAME(SET_RATE);
		MWL8K_CMDNAME(SET_FINALIZE_JOIN);
		MWL8K_CMDNAME(RTS_THRESHOLD);
		MWL8K_CMDNAME(SET_SLOT);
		MWL8K_CMDNAME(SET_EDCA_PARAMS);
		MWL8K_CMDNAME(SET_WMM_MODE);
		MWL8K_CMDNAME(MIMO_CONFIG);
		MWL8K_CMDNAME(USE_FIXED_RATE);
		MWL8K_CMDNAME(ENABLE_SNIFFER);
		MWL8K_CMDNAME(SET_MAC_ADDR);
		MWL8K_CMDNAME(SET_RATEADAPT_MODE);
		MWL8K_CMDNAME(BSS_START);
		MWL8K_CMDNAME(SET_NEW_STN);
		MWL8K_CMDNAME(UPDATE_ENCRYPTION);
		MWL8K_CMDNAME(UPDATE_STADB);
		MWL8K_CMDNAME(BASTREAM);
		MWL8K_CMDNAME(GET_WATCHDOG_BITMAP);
	default:
		snprintf(buf, bufsize, "0x%x", cmd);
	}
#undef MWL8K_CMDNAME

	return buf;
}