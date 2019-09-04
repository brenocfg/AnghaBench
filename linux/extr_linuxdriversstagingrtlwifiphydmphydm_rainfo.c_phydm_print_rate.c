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
typedef  int /*<<< orphan*/  u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int ODM_RATE54M ; 
 int ODM_RATEMCS0 ; 
 int ODM_RATEVHTSS1MCS0 ; 
 int ODM_RATEVHTSS1MCS9 ; 
 int ODM_RATEVHTSS2MCS0 ; 
 int ODM_RATEVHTSS2MCS9 ; 
 int ODM_RATEVHTSS3MCS0 ; 
 int ODM_RATEVHTSS3MCS9 ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,char*,char*,char*,char*,int,char*,char*) ; 

void phydm_print_rate(void *dm_void, u8 rate, u32 dbg_component)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 legacy_table[12] = {1, 2, 5, 11, 6, 9, 12, 18, 24, 36, 48, 54};
	u8 rate_idx = rate & 0x7f; /*remove bit7 SGI*/
	u8 vht_en = (rate_idx >= ODM_RATEVHTSS1MCS0) ? 1 : 0;
	u8 b_sgi = (rate & 0x80) >> 7;

	ODM_RT_TRACE(dm, dbg_component, "( %s%s%s%s%d%s%s)\n",
		     ((rate_idx >= ODM_RATEVHTSS1MCS0) &&
		      (rate_idx <= ODM_RATEVHTSS1MCS9)) ?
			     "VHT 1ss  " :
			     "",
		     ((rate_idx >= ODM_RATEVHTSS2MCS0) &&
		      (rate_idx <= ODM_RATEVHTSS2MCS9)) ?
			     "VHT 2ss " :
			     "",
		     ((rate_idx >= ODM_RATEVHTSS3MCS0) &&
		      (rate_idx <= ODM_RATEVHTSS3MCS9)) ?
			     "VHT 3ss " :
			     "",
		     (rate_idx >= ODM_RATEMCS0) ? "MCS " : "",
		     (vht_en) ? ((rate_idx - ODM_RATEVHTSS1MCS0) % 10) :
				((rate_idx >= ODM_RATEMCS0) ?
					 (rate_idx - ODM_RATEMCS0) :
					 ((rate_idx <= ODM_RATE54M) ?
						  legacy_table[rate_idx] :
						  0)),
		     (b_sgi) ? "-S" : "  ",
		     (rate_idx >= ODM_RATEMCS0) ? "" : "M");
}