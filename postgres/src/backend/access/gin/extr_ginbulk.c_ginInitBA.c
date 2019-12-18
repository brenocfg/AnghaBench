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
struct TYPE_3__ {int /*<<< orphan*/  tree; scalar_t__ eas_used; int /*<<< orphan*/ * entryallocator; scalar_t__ allocatedMemory; } ;
typedef  int /*<<< orphan*/  GinEntryAccumulator ;
typedef  TYPE_1__ BuildAccumulator ;

/* Variables and functions */
 int /*<<< orphan*/  cmpEntryAccumulator ; 
 int /*<<< orphan*/  ginAllocEntryAccumulator ; 
 int /*<<< orphan*/  ginCombineData ; 
 int /*<<< orphan*/  rbt_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

void
ginInitBA(BuildAccumulator *accum)
{
	/* accum->ginstate is intentionally not set here */
	accum->allocatedMemory = 0;
	accum->entryallocator = NULL;
	accum->eas_used = 0;
	accum->tree = rbt_create(sizeof(GinEntryAccumulator),
							 cmpEntryAccumulator,
							 ginCombineData,
							 ginAllocEntryAccumulator,
							 NULL,	/* no freefunc needed */
							 (void *) accum);
}