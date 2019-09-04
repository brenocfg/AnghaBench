#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int cnt_cca_all; int cnt_all; } ;
struct phy_dm_struct {int noisy_decision_smooth; int noisy_decision; TYPE_1__ false_alm_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_NOISY_DETECT ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 

void phydm_noisy_detection(struct phy_dm_struct *dm)
{
	u32 total_fa_cnt, total_cca_cnt;
	u32 score = 0, i, score_smooth;

	total_cca_cnt = dm->false_alm_cnt.cnt_cca_all;
	total_fa_cnt = dm->false_alm_cnt.cnt_all;

	for (i = 0; i <= 16; i++) {
		if (total_fa_cnt * 16 >= total_cca_cnt * (16 - i)) {
			score = 16 - i;
			break;
		}
	}

	/* noisy_decision_smooth = noisy_decision_smooth>>1 + (score<<3)>>1; */
	dm->noisy_decision_smooth =
		(dm->noisy_decision_smooth >> 1) + (score << 2);

	/* Round the noisy_decision_smooth: +"3" comes from (2^3)/2-1 */
	score_smooth = (total_cca_cnt >= 300) ?
			       ((dm->noisy_decision_smooth + 3) >> 3) :
			       0;

	dm->noisy_decision = (score_smooth >= 3) ? 1 : 0;
	ODM_RT_TRACE(
		dm, ODM_COMP_NOISY_DETECT,
		"[NoisyDetection] total_cca_cnt=%d, total_fa_cnt=%d, noisy_decision_smooth=%d, score=%d, score_smooth=%d, dm->noisy_decision=%d\n",
		total_cca_cnt, total_fa_cnt, dm->noisy_decision_smooth, score,
		score_smooth, dm->noisy_decision);
}