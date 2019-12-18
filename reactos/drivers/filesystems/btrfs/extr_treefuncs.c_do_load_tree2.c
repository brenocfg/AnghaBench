#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_3__* tree; int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ tree_holder ;
typedef  int /*<<< orphan*/  tree_data ;
struct TYPE_7__ {scalar_t__ level; } ;
struct TYPE_9__ {int /*<<< orphan*/ * paritem; TYPE_1__ header; struct TYPE_9__* parent; } ;
typedef  TYPE_3__ tree ;
typedef  int /*<<< orphan*/  root ;
typedef  int /*<<< orphan*/  device_extension ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  int3 ; 
 int /*<<< orphan*/  load_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**) ; 

__attribute__((used)) static NTSTATUS do_load_tree2(device_extension* Vcb, tree_holder* th, uint8_t* buf, root* r, tree* t, tree_data* td) {
    if (!th->tree) {
        NTSTATUS Status;
        tree* nt;

        Status = load_tree(Vcb, th->address, buf, r, &nt);
        if (!NT_SUCCESS(Status)) {
            ERR("load_tree returned %08x\n", Status);
            return Status;
        }

        nt->parent = t;

#ifdef DEBUG_PARANOID
        if (t && t->header.level <= nt->header.level) int3;
#endif

        nt->paritem = td;

        th->tree = nt;
    }

    return STATUS_SUCCESS;
}