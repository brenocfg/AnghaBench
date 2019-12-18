#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  device_extension ;
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ TREE_BLOCK_REF ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_TREE_BLOCK_REF ; 
 int /*<<< orphan*/  decrease_extent_refcount (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

NTSTATUS decrease_extent_refcount_tree(device_extension* Vcb, uint64_t address, uint64_t size, uint64_t root,
                                       uint8_t level, PIRP Irp) {
    TREE_BLOCK_REF tbr;

    tbr.offset = root;

    return decrease_extent_refcount(Vcb, address, size, TYPE_TREE_BLOCK_REF, &tbr, NULL/*FIXME*/, level, 0, false, Irp);
}