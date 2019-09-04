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
typedef  size_t u16 ;
struct rtl_sta_info {int dummy; } ;
struct phy_dm_struct {size_t* platform2phydm_macid_table; struct rtl_sta_info** odm_sta_info; } ;
typedef  enum odm_cmninfo { ____Placeholder_odm_cmninfo } odm_cmninfo ;

/* Variables and functions */
 int /*<<< orphan*/  IS_STA_VALID (struct rtl_sta_info*) ; 
#define  ODM_CMNINFO_STA_STATUS 128 

void odm_cmn_info_ptr_array_hook(struct phy_dm_struct *dm,
				 enum odm_cmninfo cmn_info, u16 index,
				 void *value)
{
	/*Hook call by reference pointer.*/
	switch (cmn_info) {
	/*Dynamic call by reference pointer.	*/
	case ODM_CMNINFO_STA_STATUS:
		dm->odm_sta_info[index] = (struct rtl_sta_info *)value;

		if (IS_STA_VALID(dm->odm_sta_info[index]))
			dm->platform2phydm_macid_table[index] = index;

		break;
	/* To remove the compiler warning, must add an empty default statement
	 * to handle the other values.
	 */
	default:
		/* do nothing */
		break;
	}
}