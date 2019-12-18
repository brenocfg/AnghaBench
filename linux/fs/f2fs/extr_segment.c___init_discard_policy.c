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
struct f2fs_sb_info {int dummy; } ;
struct discard_policy {int type; int sync; int ordered; unsigned int granularity; int io_aware; int /*<<< orphan*/  max_requests; void* max_interval; void* mid_interval; void* min_interval; scalar_t__ timeout; int /*<<< orphan*/  io_aware_gran; } ;

/* Variables and functions */
 scalar_t__ DEF_DISCARD_URGENT_UTIL ; 
 void* DEF_MAX_DISCARD_ISSUE_TIME ; 
 int /*<<< orphan*/  DEF_MAX_DISCARD_REQUEST ; 
 void* DEF_MID_DISCARD_ISSUE_TIME ; 
 void* DEF_MIN_DISCARD_ISSUE_TIME ; 
 int DPOLICY_BG ; 
 int DPOLICY_FORCE ; 
 int DPOLICY_FSTRIM ; 
 int DPOLICY_UMOUNT ; 
 int /*<<< orphan*/  MAX_PLIST_NUM ; 
 int /*<<< orphan*/  UINT_MAX ; 
 scalar_t__ utilization (struct f2fs_sb_info*) ; 

__attribute__((used)) static void __init_discard_policy(struct f2fs_sb_info *sbi,
				struct discard_policy *dpolicy,
				int discard_type, unsigned int granularity)
{
	/* common policy */
	dpolicy->type = discard_type;
	dpolicy->sync = true;
	dpolicy->ordered = false;
	dpolicy->granularity = granularity;

	dpolicy->max_requests = DEF_MAX_DISCARD_REQUEST;
	dpolicy->io_aware_gran = MAX_PLIST_NUM;
	dpolicy->timeout = 0;

	if (discard_type == DPOLICY_BG) {
		dpolicy->min_interval = DEF_MIN_DISCARD_ISSUE_TIME;
		dpolicy->mid_interval = DEF_MID_DISCARD_ISSUE_TIME;
		dpolicy->max_interval = DEF_MAX_DISCARD_ISSUE_TIME;
		dpolicy->io_aware = true;
		dpolicy->sync = false;
		dpolicy->ordered = true;
		if (utilization(sbi) > DEF_DISCARD_URGENT_UTIL) {
			dpolicy->granularity = 1;
			dpolicy->max_interval = DEF_MIN_DISCARD_ISSUE_TIME;
		}
	} else if (discard_type == DPOLICY_FORCE) {
		dpolicy->min_interval = DEF_MIN_DISCARD_ISSUE_TIME;
		dpolicy->mid_interval = DEF_MID_DISCARD_ISSUE_TIME;
		dpolicy->max_interval = DEF_MAX_DISCARD_ISSUE_TIME;
		dpolicy->io_aware = false;
	} else if (discard_type == DPOLICY_FSTRIM) {
		dpolicy->io_aware = false;
	} else if (discard_type == DPOLICY_UMOUNT) {
		dpolicy->max_requests = UINT_MAX;
		dpolicy->io_aware = false;
		/* we need to issue all to keep CP_TRIMMED_FLAG */
		dpolicy->granularity = 1;
	}
}