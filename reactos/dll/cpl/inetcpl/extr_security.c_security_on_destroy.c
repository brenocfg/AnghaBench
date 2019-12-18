#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hsec; scalar_t__ himages; int /*<<< orphan*/  hlv; struct TYPE_6__* zones; struct TYPE_6__* zone_attr; } ;
typedef  TYPE_1__ secdlg_data ;
typedef  int /*<<< orphan*/  INT_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DWLP_USER ; 
 int /*<<< orphan*/  ImageList_Destroy (scalar_t__) ; 
 int /*<<< orphan*/  LVM_SETIMAGELIST ; 
 int /*<<< orphan*/  LVSIL_NORMAL ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  security_cleanup_zones (TYPE_1__*) ; 

__attribute__((used)) static INT_PTR security_on_destroy(secdlg_data * sd)
{
    TRACE("(%p)\n", sd);

    heap_free(sd->zone_attr);
    heap_free(sd->zones);
    if (sd->himages) {
        SendMessageW(sd->hlv, LVM_SETIMAGELIST, LVSIL_NORMAL, 0);
        ImageList_Destroy(sd->himages);
    }

    security_cleanup_zones(sd);
    SetWindowLongPtrW(sd->hsec, DWLP_USER, 0);
    heap_free(sd);
    return TRUE;
}