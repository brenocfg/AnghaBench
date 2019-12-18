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
struct nlm_wait {int /*<<< orphan*/  b_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nlm_wait*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_blocked_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nlmclnt_finish_block(struct nlm_wait *block)
{
	if (block == NULL)
		return;
	spin_lock(&nlm_blocked_lock);
	list_del(&block->b_list);
	spin_unlock(&nlm_blocked_lock);
	kfree(block);
}