#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ckpt_flags; } ;
typedef  TYPE_1__ CheckpointerShmemStruct ;

/* Variables and functions */
 int CHECKPOINT_IMMEDIATE ; 
 TYPE_1__* CheckpointerShmem ; 

__attribute__((used)) static bool
ImmediateCheckpointRequested(void)
{
	volatile CheckpointerShmemStruct *cps = CheckpointerShmem;

	/*
	 * We don't need to acquire the ckpt_lck in this case because we're only
	 * looking at a single flag bit.
	 */
	if (cps->ckpt_flags & CHECKPOINT_IMMEDIATE)
		return true;
	return false;
}