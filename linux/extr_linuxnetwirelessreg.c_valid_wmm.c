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
typedef  scalar_t__ u16 ;
struct fwdb_wmm_rule {int dummy; } ;
struct fwdb_wmm_ac {int ecw; int aifsn; } ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 scalar_t__ ecw2cw (int) ; 

__attribute__((used)) static bool valid_wmm(struct fwdb_wmm_rule *rule)
{
	struct fwdb_wmm_ac *ac = (struct fwdb_wmm_ac *)rule;
	int i;

	for (i = 0; i < IEEE80211_NUM_ACS * 2; i++) {
		u16 cw_min = ecw2cw((ac[i].ecw & 0xf0) >> 4);
		u16 cw_max = ecw2cw(ac[i].ecw & 0x0f);
		u8 aifsn = ac[i].aifsn;

		if (cw_min >= cw_max)
			return false;

		if (aifsn < 1)
			return false;
	}

	return true;
}