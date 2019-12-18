#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nlm_block {TYPE_3__* b_call; } ;
struct TYPE_4__ {int /*<<< orphan*/  fl; } ;
struct TYPE_5__ {TYPE_1__ lock; } ;
struct TYPE_6__ {TYPE_2__ a_args; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,struct nlm_block*) ; 
 int locks_delete_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsvc_remove_block (struct nlm_block*) ; 

__attribute__((used)) static int nlmsvc_unlink_block(struct nlm_block *block)
{
	int status;
	dprintk("lockd: unlinking block %p...\n", block);

	/* Remove block from list */
	status = locks_delete_block(&block->b_call->a_args.lock.fl);
	nlmsvc_remove_block(block);
	return status;
}