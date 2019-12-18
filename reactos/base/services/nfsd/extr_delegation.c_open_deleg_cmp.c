#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct list_entry {int dummy; } ;
struct TYPE_5__ {void const* state; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; scalar_t__ do_close; TYPE_1__ delegation; } ;
typedef  TYPE_2__ nfs41_open_state ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireSRWLockShared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSRWLockShared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_delegated_locks (TYPE_2__*) ; 
 TYPE_2__* open_entry (struct list_entry const*) ; 

__attribute__((used)) static int open_deleg_cmp(const struct list_entry *entry, const void *value)
{
    nfs41_open_state *open = open_entry(entry);
    int result = -1;

    /* open must match the delegation and have state to reclaim */
    AcquireSRWLockShared(&open->lock);
    if (open->delegation.state != value) goto out;
    if (open->do_close && !has_delegated_locks(open)) goto out;
    result = 0;
out:
    ReleaseSRWLockShared(&open->lock);
    return result;
}