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
struct list_entry {int dummy; } ;
struct idmap_lookup {int /*<<< orphan*/  compare; int /*<<< orphan*/  value; } ;
struct idmap_cache {int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* entry_copy ) (struct list_entry*,struct list_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireSRWLockShared (int /*<<< orphan*/ *) ; 
 int ERROR_NOT_FOUND ; 
 int NO_ERROR ; 
 int /*<<< orphan*/  ReleaseSRWLockShared (int /*<<< orphan*/ *) ; 
 struct list_entry* list_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct list_entry*,struct list_entry*) ; 

__attribute__((used)) static int cache_lookup(
    struct idmap_cache *cache,
    const struct idmap_lookup *lookup,
    struct list_entry *entry_out)
{
    struct list_entry *entry;
    int status = ERROR_NOT_FOUND;

    AcquireSRWLockShared(&cache->lock);

    entry = list_search(&cache->head, lookup->value, lookup->compare);
    if (entry) {
        /* make a copy for use outside of the lock */
        cache->ops->entry_copy(entry_out, entry);
        status = NO_ERROR;
    }

    ReleaseSRWLockShared(&cache->lock);
    return status;
}