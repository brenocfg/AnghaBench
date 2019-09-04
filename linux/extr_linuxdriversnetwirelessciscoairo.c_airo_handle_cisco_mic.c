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
struct airo_info {int /*<<< orphan*/  thr_wait; int /*<<< orphan*/  jobs; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_MIC_CAPABLE ; 
 int /*<<< orphan*/  JOB_MIC ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void airo_handle_cisco_mic(struct airo_info *ai)
{
	if (test_bit(FLAG_MIC_CAPABLE, &ai->flags)) {
		set_bit(JOB_MIC, &ai->jobs);
		wake_up_interruptible(&ai->thr_wait);
	}
}