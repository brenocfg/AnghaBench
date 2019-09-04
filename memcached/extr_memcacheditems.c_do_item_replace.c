#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int it_flags; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  nkey; } ;
typedef  TYPE_1__ item ;

/* Variables and functions */
 int ITEM_SLABBED ; 
 int /*<<< orphan*/  ITEM_key (TYPE_1__*) ; 
 int /*<<< orphan*/  MEMCACHED_ITEM_REPLACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int do_item_link (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  do_item_unlink (TYPE_1__*,int /*<<< orphan*/  const) ; 

int do_item_replace(item *it, item *new_it, const uint32_t hv) {
    MEMCACHED_ITEM_REPLACE(ITEM_key(it), it->nkey, it->nbytes,
                           ITEM_key(new_it), new_it->nkey, new_it->nbytes);
    assert((it->it_flags & ITEM_SLABBED) == 0);

    do_item_unlink(it, hv);
    return do_item_link(new_it, hv);
}