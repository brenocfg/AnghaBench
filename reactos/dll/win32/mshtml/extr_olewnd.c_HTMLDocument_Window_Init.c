#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {TYPE_2__ IOleInPlaceObjectWindowless_iface; TYPE_1__ IOleInPlaceActiveObject_iface; } ;
typedef  TYPE_3__ HTMLDocument ;

/* Variables and functions */
 int /*<<< orphan*/  OleInPlaceActiveObjectVtbl ; 
 int /*<<< orphan*/  OleInPlaceObjectWindowlessVtbl ; 

void HTMLDocument_Window_Init(HTMLDocument *This)
{
    This->IOleInPlaceActiveObject_iface.lpVtbl = &OleInPlaceActiveObjectVtbl;
    This->IOleInPlaceObjectWindowless_iface.lpVtbl = &OleInPlaceObjectWindowlessVtbl;
}