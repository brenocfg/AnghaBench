#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ tree_data ;
struct TYPE_12__ {int /*<<< orphan*/  level; } ;
struct TYPE_14__ {TYPE_1__ header; int /*<<< orphan*/  root; struct TYPE_14__* parent; TYPE_2__* paritem; } ;
typedef  TYPE_3__ tree ;
struct TYPE_15__ {TYPE_2__* item; TYPE_3__* tree; } ;
typedef  TYPE_4__ traverse_ptr ;
typedef  int /*<<< orphan*/  device_extension ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  find_item_to_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* next_item (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static NTSTATUS next_item2(device_extension* Vcb, tree* t, tree_data* td, traverse_ptr* tp) {
    tree_data* td2 = next_item(t, td);
    tree* t2;

    if (td2) {
        tp->tree = t;
        tp->item = td2;
        return STATUS_SUCCESS;
    }

    t2 = t;

    do {
        td2 = t2->paritem;
        t2 = t2->parent;
    } while (td2 && !next_item(t2, td2));

    if (!td2)
        return STATUS_NOT_FOUND;

    td2 = next_item(t2, td2);

    return find_item_to_level(Vcb, t2->root, tp, &td2->key, false, t->header.level, NULL);
}