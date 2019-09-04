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

/* Variables and functions */
 int /*<<< orphan*/  CF_SET ; 
 int /*<<< orphan*/  CHALLENGE ; 
 int /*<<< orphan*/  COUNTRY ; 
 int /*<<< orphan*/  CSA ; 
 int /*<<< orphan*/  DS_SET ; 
 int /*<<< orphan*/  FH_SET ; 
 int /*<<< orphan*/  GENERIC ; 
 int /*<<< orphan*/  HOP_PARAMS ; 
 int /*<<< orphan*/  HOP_TABLE ; 
 int /*<<< orphan*/  IBSS_DFS ; 
 int /*<<< orphan*/  IBSS_SET ; 
 int /*<<< orphan*/  MEASURE_REPORT ; 
 int /*<<< orphan*/  MEASURE_REQUEST ; 
 int /*<<< orphan*/  MFIE_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWER_CAPABILITY ; 
 int /*<<< orphan*/  POWER_CONSTRAINT ; 
 int /*<<< orphan*/  QOS_PARAMETER ; 
 int /*<<< orphan*/  QUIET ; 
 int /*<<< orphan*/  RATES ; 
 int /*<<< orphan*/  RATES_EX ; 
 int /*<<< orphan*/  REQUEST ; 
 int /*<<< orphan*/  RSN ; 
 int /*<<< orphan*/  SSID ; 
 int /*<<< orphan*/  SUPP_CHANNELS ; 
 int /*<<< orphan*/  TIM ; 
 int /*<<< orphan*/  TPC_REPORT ; 
 int /*<<< orphan*/  TPC_REQUEST ; 

__attribute__((used)) static const char *get_info_element_string(u16 id)
{
	switch (id) {
		MFIE_STRING(SSID);
		MFIE_STRING(RATES);
		MFIE_STRING(FH_SET);
		MFIE_STRING(DS_SET);
		MFIE_STRING(CF_SET);
		MFIE_STRING(TIM);
		MFIE_STRING(IBSS_SET);
		MFIE_STRING(COUNTRY);
		MFIE_STRING(HOP_PARAMS);
		MFIE_STRING(HOP_TABLE);
		MFIE_STRING(REQUEST);
		MFIE_STRING(CHALLENGE);
		MFIE_STRING(POWER_CONSTRAINT);
		MFIE_STRING(POWER_CAPABILITY);
		MFIE_STRING(TPC_REQUEST);
		MFIE_STRING(TPC_REPORT);
		MFIE_STRING(SUPP_CHANNELS);
		MFIE_STRING(CSA);
		MFIE_STRING(MEASURE_REQUEST);
		MFIE_STRING(MEASURE_REPORT);
		MFIE_STRING(QUIET);
		MFIE_STRING(IBSS_DFS);
	       // MFIE_STRING(ERP_INFO);
		MFIE_STRING(RSN);
		MFIE_STRING(RATES_EX);
		MFIE_STRING(GENERIC);
		MFIE_STRING(QOS_PARAMETER);
	default:
		return "UNKNOWN";
	}
}