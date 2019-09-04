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
typedef  scalar_t__ u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKBYTE0 ; 
 int ODM_RTL8192E ; 
 int ODM_RTL8812 ; 
 int ODM_RTL8822B ; 
 scalar_t__ PHYDM_A ; 
 scalar_t__ PHYDM_AB ; 
 scalar_t__ PHYDM_B ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int) ; 

void phydm_config_ofdm_rx_path(struct phy_dm_struct *dm, u32 path)
{
	u8 ofdm_rx_path = 0;

	if (dm->support_ic_type & (ODM_RTL8192E)) {
	} else if (dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8822B)) {
		if (path == PHYDM_A) {
			ofdm_rx_path = 1;
			/**/
		} else if (path == PHYDM_B) {
			ofdm_rx_path = 2;
			/**/
		} else if (path == PHYDM_AB) {
			ofdm_rx_path = 3;
			/**/
		}

		odm_set_bb_reg(dm, 0x808, MASKBYTE0,
			       ((ofdm_rx_path << 4) | ofdm_rx_path));
	}
}