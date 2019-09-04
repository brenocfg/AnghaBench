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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_ADDRESS ; 
 int /*<<< orphan*/  AIRONET_INFO ; 
 int /*<<< orphan*/  AP_TX_POWER ; 
 int /*<<< orphan*/  ASSOCIATE ; 
 int /*<<< orphan*/  CARD_DISABLE ; 
 int /*<<< orphan*/  CCKM_INFO ; 
 int /*<<< orphan*/  CCX_VER_INFO ; 
 int /*<<< orphan*/  COUNTRY_INFO ; 
 int /*<<< orphan*/  DINO_CONFIG ; 
 int /*<<< orphan*/  EXT_SUPPORTED_RATES ; 
 int /*<<< orphan*/  FRAG_THRESHOLD ; 
 int /*<<< orphan*/  HOST_COMPLETE ; 
 int /*<<< orphan*/  IPW_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPW_PRE_POWER_DOWN ; 
 int /*<<< orphan*/  MEASUREMENT ; 
 int /*<<< orphan*/  MULTICAST_ADDRESS ; 
 int /*<<< orphan*/  PORT_TYPE ; 
 int /*<<< orphan*/  POWER_CAPABILITY ; 
 int /*<<< orphan*/  POWER_DOWN ; 
 int /*<<< orphan*/  POWER_MODE ; 
 int /*<<< orphan*/  PRODUCTION_COMMAND ; 
 int /*<<< orphan*/  QOS_PARAMETERS ; 
 int /*<<< orphan*/  RETRY_LIMIT ; 
 int /*<<< orphan*/  RSN_CAPABILITIES ; 
 int /*<<< orphan*/  RTS_THRESHOLD ; 
 int /*<<< orphan*/  RX_KEY ; 
 int /*<<< orphan*/  SCAN_ABORT ; 
 int /*<<< orphan*/  SCAN_REQUEST ; 
 int /*<<< orphan*/  SCAN_REQUEST_EXT ; 
 int /*<<< orphan*/  SEED_NUMBER ; 
 int /*<<< orphan*/  SENSITIVITY_CALIB ; 
 int /*<<< orphan*/  SET_CALIBRATION ; 
 int /*<<< orphan*/  SSID ; 
 int /*<<< orphan*/  SUPPORTED_CHANNELS ; 
 int /*<<< orphan*/  SUPPORTED_RATES ; 
 int /*<<< orphan*/  SYSTEM_CONFIG ; 
 int /*<<< orphan*/  TGI_TX_KEY ; 
 int /*<<< orphan*/  TPC_REPORT ; 
 int /*<<< orphan*/  TX_FLUSH ; 
 int /*<<< orphan*/  TX_POWER ; 
 int /*<<< orphan*/  VAP_BEACON_TEMPLATE ; 
 int /*<<< orphan*/  VAP_CELL_PWR_LIMIT ; 
 int /*<<< orphan*/  VAP_CF_PARAM_SET ; 
 int /*<<< orphan*/  VAP_CHANNEL_SWITCH ; 
 int /*<<< orphan*/  VAP_DTIM_PERIOD ; 
 int /*<<< orphan*/  VAP_LOCAL_TX_PWR_CONSTRAINT ; 
 int /*<<< orphan*/  VAP_MANDATORY_CHANNELS ; 
 int /*<<< orphan*/  VAP_QUIET_INTERVALS ; 
 int /*<<< orphan*/  VAP_SET_BEACONING_STATE ; 
 int /*<<< orphan*/  WEP_KEY ; 
 int /*<<< orphan*/  WME_INFO ; 

__attribute__((used)) static char *get_cmd_string(u8 cmd)
{
	switch (cmd) {
		IPW_CMD(HOST_COMPLETE);
		IPW_CMD(POWER_DOWN);
		IPW_CMD(SYSTEM_CONFIG);
		IPW_CMD(MULTICAST_ADDRESS);
		IPW_CMD(SSID);
		IPW_CMD(ADAPTER_ADDRESS);
		IPW_CMD(PORT_TYPE);
		IPW_CMD(RTS_THRESHOLD);
		IPW_CMD(FRAG_THRESHOLD);
		IPW_CMD(POWER_MODE);
		IPW_CMD(WEP_KEY);
		IPW_CMD(TGI_TX_KEY);
		IPW_CMD(SCAN_REQUEST);
		IPW_CMD(SCAN_REQUEST_EXT);
		IPW_CMD(ASSOCIATE);
		IPW_CMD(SUPPORTED_RATES);
		IPW_CMD(SCAN_ABORT);
		IPW_CMD(TX_FLUSH);
		IPW_CMD(QOS_PARAMETERS);
		IPW_CMD(DINO_CONFIG);
		IPW_CMD(RSN_CAPABILITIES);
		IPW_CMD(RX_KEY);
		IPW_CMD(CARD_DISABLE);
		IPW_CMD(SEED_NUMBER);
		IPW_CMD(TX_POWER);
		IPW_CMD(COUNTRY_INFO);
		IPW_CMD(AIRONET_INFO);
		IPW_CMD(AP_TX_POWER);
		IPW_CMD(CCKM_INFO);
		IPW_CMD(CCX_VER_INFO);
		IPW_CMD(SET_CALIBRATION);
		IPW_CMD(SENSITIVITY_CALIB);
		IPW_CMD(RETRY_LIMIT);
		IPW_CMD(IPW_PRE_POWER_DOWN);
		IPW_CMD(VAP_BEACON_TEMPLATE);
		IPW_CMD(VAP_DTIM_PERIOD);
		IPW_CMD(EXT_SUPPORTED_RATES);
		IPW_CMD(VAP_LOCAL_TX_PWR_CONSTRAINT);
		IPW_CMD(VAP_QUIET_INTERVALS);
		IPW_CMD(VAP_CHANNEL_SWITCH);
		IPW_CMD(VAP_MANDATORY_CHANNELS);
		IPW_CMD(VAP_CELL_PWR_LIMIT);
		IPW_CMD(VAP_CF_PARAM_SET);
		IPW_CMD(VAP_SET_BEACONING_STATE);
		IPW_CMD(MEASUREMENT);
		IPW_CMD(POWER_CAPABILITY);
		IPW_CMD(SUPPORTED_CHANNELS);
		IPW_CMD(TPC_REPORT);
		IPW_CMD(WME_INFO);
		IPW_CMD(PRODUCTION_COMMAND);
	default:
		return "UNKNOWN";
	}
}