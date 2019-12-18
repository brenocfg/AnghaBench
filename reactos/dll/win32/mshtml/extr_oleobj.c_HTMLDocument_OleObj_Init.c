#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_15__ {TYPE_2__ IObjectSafety_iface; TYPE_1__ IOleContainer_iface; TYPE_6__ IObjectWithSite_iface; TYPE_5__ IOleControl_iface; TYPE_4__ IOleDocument_iface; TYPE_3__ IOleObject_iface; } ;
typedef  TYPE_7__ HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  ObjectSafetyVtbl ; 
 int /*<<< orphan*/  ObjectWithSiteVtbl ; 
 int /*<<< orphan*/  OleContainerVtbl ; 
 int /*<<< orphan*/  OleControlVtbl ; 
 int /*<<< orphan*/  OleDocumentVtbl ; 
 int /*<<< orphan*/  OleObjectVtbl ; 

void HTMLDocument_OleObj_Init(HTMLDocument *This)
{
    This->IOleObject_iface.lpVtbl = &OleObjectVtbl;
    This->IOleDocument_iface.lpVtbl = &OleDocumentVtbl;
    This->IOleControl_iface.lpVtbl = &OleControlVtbl;
    This->IObjectWithSite_iface.lpVtbl = &ObjectWithSiteVtbl;
    This->IOleContainer_iface.lpVtbl = &OleContainerVtbl;
    This->IObjectSafety_iface.lpVtbl = &ObjectSafetyVtbl;
}