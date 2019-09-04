#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t max_slots; int* seq_nums; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; scalar_t__ target_delay; scalar_t__ num_used; scalar_t__ highest_used; scalar_t__* used_slots; } ;
typedef  TYPE_1__ nfs41_slot_table ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 size_t NFS41_MAX_NUM_SLOTS ; 
 int /*<<< orphan*/  WakeAllConditionVariable (int /*<<< orphan*/ *) ; 
 scalar_t__ slot_table_avail (TYPE_1__*) ; 

__attribute__((used)) static void init_slot_table(nfs41_slot_table *table) 
{
    uint32_t i;
    EnterCriticalSection(&table->lock);
    table->max_slots = NFS41_MAX_NUM_SLOTS;
    for (i = 0; i < NFS41_MAX_NUM_SLOTS; i++) {
        table->seq_nums[i] = 1;
        table->used_slots[i] = 0;
    }
    table->highest_used = table->num_used = 0;
    table->target_delay = 0;

    /* wake any threads waiting on a slot */
    if (slot_table_avail(table))
        WakeAllConditionVariable(&table->cond);
    LeaveCriticalSection(&table->lock);
}