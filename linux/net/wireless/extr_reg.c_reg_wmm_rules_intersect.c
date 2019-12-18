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
struct ieee80211_wmm_ac {void* aifsn; int /*<<< orphan*/  cot; void* cw_max; void* cw_min; } ;

/* Variables and functions */
 void* max_t (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static void reg_wmm_rules_intersect(const struct ieee80211_wmm_ac *wmm_ac1,
				    const struct ieee80211_wmm_ac *wmm_ac2,
				    struct ieee80211_wmm_ac *intersect)
{
	intersect->cw_min = max_t(u16, wmm_ac1->cw_min, wmm_ac2->cw_min);
	intersect->cw_max = max_t(u16, wmm_ac1->cw_max, wmm_ac2->cw_max);
	intersect->cot = min_t(u16, wmm_ac1->cot, wmm_ac2->cot);
	intersect->aifsn = max_t(u8, wmm_ac1->aifsn, wmm_ac2->aifsn);
}