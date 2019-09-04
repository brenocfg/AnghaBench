#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  nkey; } ;
typedef  TYPE_1__ item ;
typedef  enum store_item_type { ____Placeholder_store_item_type } store_item_type ;
typedef  int /*<<< orphan*/  conn ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_key (TYPE_1__*) ; 
 int do_store_item (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_unlock (int /*<<< orphan*/ ) ; 

enum store_item_type store_item(item *item, int comm, conn* c) {
    enum store_item_type ret;
    uint32_t hv;

    hv = hash(ITEM_key(item), item->nkey);
    item_lock(hv);
    ret = do_store_item(item, comm, c, hv);
    item_unlock(hv);
    return ret;
}