#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
struct TYPE_7__ {scalar_t__ reserved; TYPE_1__ root_item; } ;
typedef  TYPE_2__ root ;
struct TYPE_8__ {scalar_t__ RequestorMode; } ;
typedef  TYPE_3__* PIRP ;

/* Variables and functions */
 int BTRFS_SUBVOL_READONLY ; 
 scalar_t__ PsGetCurrentProcess () ; 
 scalar_t__ UserMode ; 

__attribute__((used)) __inline static bool is_subvol_readonly(root* r, PIRP Irp) {
    if (!(r->root_item.flags & BTRFS_SUBVOL_READONLY))
        return false;

    if (!r->reserved)
        return true;

    return (!Irp || Irp->RequestorMode == UserMode) && PsGetCurrentProcess() != r->reserved ? true : false;
}