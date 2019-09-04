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
struct f2fs_sb_info {int dummy; } ;
struct cp_control {int /*<<< orphan*/  trim_start; int /*<<< orphan*/  trim_end; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  sentry_lock; } ;

/* Variables and functions */
 TYPE_1__* SIT_I (struct f2fs_sb_info*) ; 
 scalar_t__ add_discard_addrs (struct f2fs_sb_info*,struct cp_control*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

bool f2fs_exist_trim_candidates(struct f2fs_sb_info *sbi,
						struct cp_control *cpc)
{
	__u64 trim_start = cpc->trim_start;
	bool has_candidate = false;

	down_write(&SIT_I(sbi)->sentry_lock);
	for (; cpc->trim_start <= cpc->trim_end; cpc->trim_start++) {
		if (add_discard_addrs(sbi, cpc, true)) {
			has_candidate = true;
			break;
		}
	}
	up_write(&SIT_I(sbi)->sentry_lock);

	cpc->trim_start = trim_start;
	return has_candidate;
}