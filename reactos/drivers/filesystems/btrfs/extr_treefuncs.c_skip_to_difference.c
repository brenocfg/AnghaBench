#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ tree_data ;
struct TYPE_11__ {scalar_t__ address; } ;
struct TYPE_13__ {int /*<<< orphan*/  root; TYPE_1__ header; struct TYPE_13__* parent; TYPE_2__* paritem; } ;
typedef  TYPE_3__ tree ;
struct TYPE_14__ {TYPE_2__* item; TYPE_3__* tree; } ;
typedef  TYPE_4__ traverse_ptr ;
typedef  int /*<<< orphan*/  device_extension ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  find_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_item2 (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,TYPE_4__*) ; 

NTSTATUS skip_to_difference(device_extension* Vcb, traverse_ptr* tp, traverse_ptr* tp2, bool* ended1, bool* ended2) {
    NTSTATUS Status;
    tree *t1, *t2;
    tree_data *td1, *td2;

    t1 = tp->tree;
    t2 = tp2->tree;

    do {
        td1 = t1->paritem;
        td2 = t2->paritem;
        t1 = t1->parent;
        t2 = t2->parent;
    } while (t1 && t2 && t1->header.address == t2->header.address);

    while (true) {
        traverse_ptr tp3, tp4;

        Status = next_item2(Vcb, t1, td1, &tp3);
        if (Status == STATUS_NOT_FOUND)
            *ended1 = true;
        else if (!NT_SUCCESS(Status)) {
            ERR("next_item2 returned %08x\n", Status);
            return Status;
        }

        Status = next_item2(Vcb, t2, td2, &tp4);
        if (Status == STATUS_NOT_FOUND)
            *ended2 = true;
        else if (!NT_SUCCESS(Status)) {
            ERR("next_item2 returned %08x\n", Status);
            return Status;
        }

        if (*ended1 || *ended2) {
            if (!*ended1) {
                Status = find_item(Vcb, t1->root, tp, &tp3.item->key, false, NULL);
                if (!NT_SUCCESS(Status)) {
                    ERR("find_item returned %08x\n", Status);
                    return Status;
                }
            } else if (!*ended2) {
                Status = find_item(Vcb, t2->root, tp2, &tp4.item->key, false, NULL);
                if (!NT_SUCCESS(Status)) {
                    ERR("find_item returned %08x\n", Status);
                    return Status;
                }
            }

            return STATUS_SUCCESS;
        }

        if (tp3.tree->header.address != tp4.tree->header.address) {
            Status = find_item(Vcb, t1->root, tp, &tp3.item->key, false, NULL);
            if (!NT_SUCCESS(Status)) {
                ERR("find_item returned %08x\n", Status);
                return Status;
            }

            Status = find_item(Vcb, t2->root, tp2, &tp4.item->key, false, NULL);
            if (!NT_SUCCESS(Status)) {
                ERR("find_item returned %08x\n", Status);
                return Status;
            }

            return STATUS_SUCCESS;
        }

        t1 = tp3.tree;
        td1 = tp3.item;
        t2 = tp4.tree;
        td2 = tp4.item;
    }
}