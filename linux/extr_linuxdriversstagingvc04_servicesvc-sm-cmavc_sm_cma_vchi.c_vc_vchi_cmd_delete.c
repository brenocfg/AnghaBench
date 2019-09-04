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
struct sm_instance {int /*<<< orphan*/  free_sema; int /*<<< orphan*/  free_lock; int /*<<< orphan*/  free_list; } ;
struct sm_cmd_rsp_blk {int /*<<< orphan*/  head; scalar_t__ alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sm_cmd_rsp_blk*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vc_vchi_cmd_delete(struct sm_instance *instance, struct sm_cmd_rsp_blk *blk)
{
	if (blk->alloc) {
		kfree(blk);
		return;
	}

	mutex_lock(&instance->free_lock);
	list_add(&blk->head, &instance->free_list);
	mutex_unlock(&instance->free_lock);
	up(&instance->free_sema);
}