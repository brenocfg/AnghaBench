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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_RA_MASK ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 scalar_t__ PHYDM_WIRELESS_MODE_AC_24G ; 
 scalar_t__ PHYDM_WIRELESS_MODE_AC_5G ; 
 scalar_t__ PHYDM_WIRELESS_MODE_AC_ONLY ; 

u8 phydm_vht_en_mapping(void *dm_void, u32 wireless_mode)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 vht_en_out = 0;

	if ((wireless_mode == PHYDM_WIRELESS_MODE_AC_5G) ||
	    (wireless_mode == PHYDM_WIRELESS_MODE_AC_24G) ||
	    (wireless_mode == PHYDM_WIRELESS_MODE_AC_ONLY)) {
		vht_en_out = 1;
		/**/
	}

	ODM_RT_TRACE(dm, ODM_COMP_RA_MASK,
		     "wireless_mode= (( 0x%x )), VHT_EN= (( %d ))\n",
		     wireless_mode, vht_en_out);
	return vht_en_out;
}