#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* ext; int /*<<< orphan*/ * fcb; } ;
typedef  TYPE_1__ rollback_extent ;
typedef  int /*<<< orphan*/  fcb ;
struct TYPE_7__ {int ignore; } ;
typedef  TYPE_2__ extent ;
typedef  int /*<<< orphan*/  LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  ERR (char*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ROLLBACK_DELETE_EXTENT ; 
 int /*<<< orphan*/  add_rollback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void remove_fcb_extent(fcb* fcb, extent* ext, LIST_ENTRY* rollback) {
    if (!ext->ignore) {
        rollback_extent* re;

        ext->ignore = true;

        re = ExAllocatePoolWithTag(NonPagedPool, sizeof(rollback_extent), ALLOC_TAG);
        if (!re) {
            ERR("out of memory\n");
            return;
        }

        re->fcb = fcb;
        re->ext = ext;

        add_rollback(rollback, ROLLBACK_DELETE_EXTENT, re);
    }
}