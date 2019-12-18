#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int refs; TYPE_1__ IDropTarget_iface; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ IDropTarget ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ DropTargetWrapper ;

/* Variables and functions */
 int /*<<< orphan*/  DropTargetWrapperVTbl ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static IDropTarget* WrapDropTarget( HWND hwnd )
{
    DropTargetWrapper* This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));

    if (This)
    {
        This->IDropTarget_iface.lpVtbl = &DropTargetWrapperVTbl;
        This->hwnd = hwnd;
        This->refs = 1;
    }
    return &This->IDropTarget_iface;
}