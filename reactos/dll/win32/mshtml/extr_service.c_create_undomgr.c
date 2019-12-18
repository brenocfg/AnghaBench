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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IOleUndoManager_iface; } ;
typedef  TYPE_1__ UndoManager ;
typedef  TYPE_2__ IOleUndoManager ;

/* Variables and functions */
 int /*<<< orphan*/  OleUndoManagerVtbl ; 
 TYPE_1__* heap_alloc (int) ; 

__attribute__((used)) static IOleUndoManager *create_undomgr(void)
{
    UndoManager *ret = heap_alloc(sizeof(UndoManager));

    if (!ret) return NULL;

    ret->IOleUndoManager_iface.lpVtbl = &OleUndoManagerVtbl;
    ret->ref = 1;

    return &ret->IOleUndoManager_iface;
}