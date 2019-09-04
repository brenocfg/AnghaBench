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
typedef  int u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int ODM_RTL8197F ; 
 int ODM_RTL8821C ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  phydm_check_dmval_txagc (struct phy_dm_struct*,int,int,int* const,char*) ; 

__attribute__((used)) static void phydm_set_txagc(void *dm_void, u32 *const dm_value, u32 *_used,
			    char *output, u32 *_out_len)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 used = *_used;
	u32 out_len = *_out_len;

	/*dm_value[1] = path*/
	/*dm_value[2] = hw_rate*/
	/*dm_value[3] = power_index*/

	if (dm->support_ic_type &
	    (ODM_RTL8822B | ODM_RTL8197F | ODM_RTL8821C)) {
		if (dm_value[1] <= 1) {
			phydm_check_dmval_txagc(dm, used, out_len, dm_value,
						output);
		} else {
			PHYDM_SNPRINTF(output + used, out_len - used,
				       "  %s%d   %s%x%s\n", "Write path-",
				       (dm_value[1] & 0x1), "rate index-0x",
				       (dm_value[2] & 0x7f), " fail");
		}
	}
}