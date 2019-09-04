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
struct nlm_wait {int /*<<< orphan*/  b_list; int /*<<< orphan*/  b_status; int /*<<< orphan*/  b_wait; struct file_lock* b_lock; struct nlm_host* b_host; } ;
struct nlm_host {int dummy; } ;
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct nlm_wait* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_blocked ; 
 int /*<<< orphan*/  nlm_blocked_lock ; 
 int /*<<< orphan*/  nlm_lck_blocked ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nlm_wait *nlmclnt_prepare_block(struct nlm_host *host, struct file_lock *fl)
{
	struct nlm_wait *block;

	block = kmalloc(sizeof(*block), GFP_KERNEL);
	if (block != NULL) {
		block->b_host = host;
		block->b_lock = fl;
		init_waitqueue_head(&block->b_wait);
		block->b_status = nlm_lck_blocked;

		spin_lock(&nlm_blocked_lock);
		list_add(&block->b_list, &nlm_blocked);
		spin_unlock(&nlm_blocked_lock);
	}
	return block;
}