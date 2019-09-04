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
typedef  enum rf_type { ____Placeholder_rf_type } rf_type ;
typedef  enum halmac_rf_type { ____Placeholder_halmac_rf_type } halmac_rf_type ;

/* Variables and functions */
 int HALMAC_RF_1T1R ; 
 int HALMAC_RF_1T2R ; 
 int HALMAC_RF_2T2R ; 
 int HALMAC_RF_2T2R_GREEN ; 
#define  RF_1T1R 131 
#define  RF_1T2R 130 
#define  RF_2T2R 129 
#define  RF_2T2R_GREEN 128 

__attribute__((used)) static inline enum halmac_rf_type _rf_type_drv2halmac(enum rf_type rf_drv)
{
	enum halmac_rf_type rf_mac;

	switch (rf_drv) {
	case RF_1T2R:
		rf_mac = HALMAC_RF_1T2R;
		break;
	case RF_2T2R:
		rf_mac = HALMAC_RF_2T2R;
		break;
	case RF_1T1R:
		rf_mac = HALMAC_RF_1T1R;
		break;
	case RF_2T2R_GREEN:
		rf_mac = HALMAC_RF_2T2R_GREEN;
		break;
	default:
		rf_mac = (enum halmac_rf_type)rf_drv;
		break;
	}

	return rf_mac;
}