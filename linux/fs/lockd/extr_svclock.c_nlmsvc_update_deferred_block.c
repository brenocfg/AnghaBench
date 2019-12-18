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
struct nlm_block {int b_granted; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_GOT_CALLBACK ; 
 int /*<<< orphan*/  B_TIMED_OUT ; 

__attribute__((used)) static void
nlmsvc_update_deferred_block(struct nlm_block *block, int result)
{
	block->b_flags |= B_GOT_CALLBACK;
	if (result == 0)
		block->b_granted = 1;
	else
		block->b_flags |= B_TIMED_OUT;
}