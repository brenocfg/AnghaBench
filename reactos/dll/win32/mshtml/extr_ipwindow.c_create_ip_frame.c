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
struct TYPE_5__ {int ref; TYPE_2__ IOleInPlaceFrame_iface; } ;
typedef  TYPE_1__ InPlaceFrame ;
typedef  TYPE_2__ IOleInPlaceFrame ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  OleInPlaceFrameVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_1__* heap_alloc_zero (int) ; 

HRESULT create_ip_frame(IOleInPlaceFrame **ret)
{
    InPlaceFrame *frame;

    frame = heap_alloc_zero(sizeof(*frame));
    if(!frame)
        return E_OUTOFMEMORY;

    frame->IOleInPlaceFrame_iface.lpVtbl = &OleInPlaceFrameVtbl;
    frame->ref = 1;

    *ret = &frame->IOleInPlaceFrame_iface;
    return S_OK;
}