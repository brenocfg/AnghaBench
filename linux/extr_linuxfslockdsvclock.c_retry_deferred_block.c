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
struct nlm_block {int b_flags; TYPE_1__* b_deferred_req; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* revisit ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int B_GOT_CALLBACK ; 
 int B_TIMED_OUT ; 
 int /*<<< orphan*/  NLM_TIMEOUT ; 
 int /*<<< orphan*/  dprintk (char*,struct nlm_block*,int) ; 
 int /*<<< orphan*/  nlmsvc_insert_block (struct nlm_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
retry_deferred_block(struct nlm_block *block)
{
	if (!(block->b_flags & B_GOT_CALLBACK))
		block->b_flags |= B_TIMED_OUT;
	nlmsvc_insert_block(block, NLM_TIMEOUT);
	dprintk("revisit block %p flags %d\n",	block, block->b_flags);
	if (block->b_deferred_req) {
		block->b_deferred_req->revisit(block->b_deferred_req, 0);
		block->b_deferred_req = NULL;
	}
}