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
struct airo_info {int /*<<< orphan*/  thr_wait; int /*<<< orphan*/  expires; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_RADIO_DOWN ; 
 int HZ ; 
 int /*<<< orphan*/  RUN_AT (int) ; 
 scalar_t__ auto_wep ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void try_auto_wep(struct airo_info *ai)
{
	if (auto_wep && !test_bit(FLAG_RADIO_DOWN, &ai->flags)) {
		ai->expires = RUN_AT(3*HZ);
		wake_up_interruptible(&ai->thr_wait);
	}
}