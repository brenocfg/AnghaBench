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
struct network_info {int /*<<< orphan*/  bssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGING_TIME ; 
 int /*<<< orphan*/  aging_timer ; 
 scalar_t__ jiffies ; 
 int last_scanned_cnt ; 
 TYPE_1__* last_scanned_shadow ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_network_in_shadow(struct network_info *nw_info, void *user_void)
{
	int state = -1;
	int i;

	if (last_scanned_cnt == 0) {
		mod_timer(&aging_timer, jiffies + msecs_to_jiffies(AGING_TIME));
		state = -1;
	} else {
		for (i = 0; i < last_scanned_cnt; i++) {
			if (memcmp(last_scanned_shadow[i].bssid,
				   nw_info->bssid, 6) == 0) {
				state = i;
				break;
			}
		}
	}
	return state;
}