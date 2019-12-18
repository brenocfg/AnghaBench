#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  nkey; struct TYPE_6__* h_next; } ;
typedef  TYPE_1__ item ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_key (TYPE_1__*) ; 
 int /*<<< orphan*/  MEMCACHED_ASSOC_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int expand_bucket ; 
 scalar_t__ expanding ; 
 size_t const hashmask (scalar_t__) ; 
 scalar_t__ hashpower ; 
 TYPE_1__** old_hashtable ; 
 TYPE_1__** primary_hashtable ; 

int assoc_insert(item *it, const uint32_t hv) {
    unsigned int oldbucket;

//    assert(assoc_find(ITEM_key(it), it->nkey) == 0);  /* shouldn't have duplicately named things defined */

    if (expanding &&
        (oldbucket = (hv & hashmask(hashpower - 1))) >= expand_bucket)
    {
        it->h_next = old_hashtable[oldbucket];
        old_hashtable[oldbucket] = it;
    } else {
        it->h_next = primary_hashtable[hv & hashmask(hashpower)];
        primary_hashtable[hv & hashmask(hashpower)] = it;
    }

    MEMCACHED_ASSOC_INSERT(ITEM_key(it), it->nkey);
    return 1;
}