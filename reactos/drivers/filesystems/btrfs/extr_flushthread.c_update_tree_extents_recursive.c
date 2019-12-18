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
struct TYPE_4__ {struct TYPE_4__* parent; scalar_t__ has_address; int /*<<< orphan*/  updated_extents; } ;
typedef  TYPE_1__ tree ;
typedef  int /*<<< orphan*/  device_extension ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  update_tree_extents (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS update_tree_extents_recursive(device_extension* Vcb, tree* t, PIRP Irp, LIST_ENTRY* rollback) {
    NTSTATUS Status;

    if (t->parent && !t->parent->updated_extents && t->parent->has_address) {
        Status = update_tree_extents_recursive(Vcb, t->parent, Irp, rollback);
        if (!NT_SUCCESS(Status))
            return Status;
    }

    Status = update_tree_extents(Vcb, t, Irp, rollback);
    if (!NT_SUCCESS(Status)) {
        ERR("update_tree_extents returned %08x\n", Status);
        return Status;
    }

    return STATUS_SUCCESS;
}