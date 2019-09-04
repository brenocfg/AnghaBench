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
struct lpfc_hba {int /*<<< orphan*/  fabric_block_timer; int /*<<< orphan*/  bit_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FABRIC_COMANDS_BLOCKED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_block_fabric_iocbs(struct lpfc_hba *phba)
{
	int blocked;

	blocked = test_and_set_bit(FABRIC_COMANDS_BLOCKED, &phba->bit_flags);
	/* Start a timer to unblock fabric iocbs after 100ms */
	if (!blocked)
		mod_timer(&phba->fabric_block_timer,
			  jiffies + msecs_to_jiffies(100));

	return;
}