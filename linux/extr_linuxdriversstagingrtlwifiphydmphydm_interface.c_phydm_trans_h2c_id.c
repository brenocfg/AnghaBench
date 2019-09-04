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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
#define  ODM_H2C_IQ_CALIBRATION 135 
#define  ODM_H2C_RA_PARA_ADJUST 134 
#define  ODM_H2C_RSSI_REPORT 133 
#define  ODM_H2C_WIFI_CALIBRATION 132 
#define  PHYDM_H2C_DYNAMIC_TX_PATH 131 
#define  PHYDM_H2C_FW_TRACE_EN 130 
#define  PHYDM_H2C_MU 129 
#define  PHYDM_H2C_TXBF 128 

__attribute__((used)) static u8 phydm_trans_h2c_id(struct phy_dm_struct *dm, u8 phydm_h2c_id)
{
	u8 platform_h2c_id = phydm_h2c_id;

	switch (phydm_h2c_id) {
	/* 1 [0] */
	case ODM_H2C_RSSI_REPORT:

		break;

	/* 1 [3] */
	case ODM_H2C_WIFI_CALIBRATION:

		break;

	/* 1 [4] */
	case ODM_H2C_IQ_CALIBRATION:

		break;
	/* 1 [5] */
	case ODM_H2C_RA_PARA_ADJUST:

		break;

	/* 1 [6] */
	case PHYDM_H2C_DYNAMIC_TX_PATH:

		break;

	/* [7]*/
	case PHYDM_H2C_FW_TRACE_EN:

		platform_h2c_id = 0x49;

		break;

	case PHYDM_H2C_TXBF:
		break;

	case PHYDM_H2C_MU:
		platform_h2c_id = 0x4a; /*H2C_MU*/
		break;

	default:
		platform_h2c_id = phydm_h2c_id;
		break;
	}

	return platform_h2c_id;
}