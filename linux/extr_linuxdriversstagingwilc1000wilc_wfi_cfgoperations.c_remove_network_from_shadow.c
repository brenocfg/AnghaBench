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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * join_params; int /*<<< orphan*/ * ies; scalar_t__ time_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGING_TIME ; 
 scalar_t__ SCAN_RESULT_EXPIRE ; 
 int /*<<< orphan*/  aging_timer ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int last_scanned_cnt ; 
 TYPE_1__* last_scanned_shadow ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static void remove_network_from_shadow(struct timer_list *unused)
{
	unsigned long now = jiffies;
	int i, j;

	for (i = 0; i < last_scanned_cnt; i++) {
		if (!time_after(now, last_scanned_shadow[i].time_scan +
				(unsigned long)(SCAN_RESULT_EXPIRE)))
			continue;
		kfree(last_scanned_shadow[i].ies);
		last_scanned_shadow[i].ies = NULL;

		kfree(last_scanned_shadow[i].join_params);

		for (j = i; (j < last_scanned_cnt - 1); j++)
			last_scanned_shadow[j] = last_scanned_shadow[j + 1];

		last_scanned_cnt--;
	}

	if (last_scanned_cnt != 0)
		mod_timer(&aging_timer, jiffies + msecs_to_jiffies(AGING_TIME));
}