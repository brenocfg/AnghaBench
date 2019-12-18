#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* item; } ;
typedef  TYPE_3__ traverse_ptr ;
struct TYPE_13__ {int /*<<< orphan*/  parent; TYPE_8__* Vcb; int /*<<< orphan*/  root; TYPE_1__* send; int /*<<< orphan*/  buffer_event; } ;
typedef  TYPE_4__ send_context ;
struct TYPE_14__ {int /*<<< orphan*/  tree_lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  key; } ;
struct TYPE_10__ {scalar_t__ cancelling; int /*<<< orphan*/  cleared_event; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  KeClearEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  find_item (TYPE_8__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ keycmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS wait_for_flush(send_context* context, traverse_ptr* tp1, traverse_ptr* tp2) {
    NTSTATUS Status;
    KEY key1, key2;

    if (tp1)
        key1 = tp1->item->key;

    if (tp2)
        key2 = tp2->item->key;

    ExReleaseResourceLite(&context->Vcb->tree_lock);

    KeClearEvent(&context->send->cleared_event);
    KeSetEvent(&context->buffer_event, 0, true);
    KeWaitForSingleObject(&context->send->cleared_event, Executive, KernelMode, false, NULL);

    ExAcquireResourceSharedLite(&context->Vcb->tree_lock, true);

    if (context->send->cancelling)
        return STATUS_SUCCESS;

    if (tp1) {
        Status = find_item(context->Vcb, context->root, tp1, &key1, false, NULL);
        if (!NT_SUCCESS(Status)) {
            ERR("find_item returned %08x\n", Status);
            return Status;
        }

        if (keycmp(tp1->item->key, key1)) {
            ERR("readonly subvolume changed\n");
            return STATUS_INTERNAL_ERROR;
        }
    }

    if (tp2) {
        Status = find_item(context->Vcb, context->parent, tp2, &key2, false, NULL);
        if (!NT_SUCCESS(Status)) {
            ERR("find_item returned %08x\n", Status);
            return Status;
        }

        if (keycmp(tp2->item->key, key2)) {
            ERR("readonly subvolume changed\n");
            return STATUS_INTERNAL_ERROR;
        }
    }

    return STATUS_SUCCESS;
}