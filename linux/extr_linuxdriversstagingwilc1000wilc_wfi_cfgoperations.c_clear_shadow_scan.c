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
struct TYPE_2__ {int /*<<< orphan*/ * join_params; int /*<<< orphan*/ * ies; } ;

/* Variables and functions */
 int /*<<< orphan*/  aging_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int last_scanned_cnt ; 
 TYPE_1__* last_scanned_shadow ; 
 scalar_t__ op_ifcs ; 

__attribute__((used)) static void clear_shadow_scan(void)
{
	int i;

	if (op_ifcs != 0)
		return;

	del_timer_sync(&aging_timer);

	for (i = 0; i < last_scanned_cnt; i++) {
		if (last_scanned_shadow[last_scanned_cnt].ies) {
			kfree(last_scanned_shadow[i].ies);
			last_scanned_shadow[last_scanned_cnt].ies = NULL;
		}

		kfree(last_scanned_shadow[i].join_params);
		last_scanned_shadow[i].join_params = NULL;
	}
	last_scanned_cnt = 0;
}