#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_13__ {int /*<<< orphan*/  control; scalar_t__ fInPlace; TYPE_2__ size; } ;
struct TYPE_11__ {scalar_t__ cy; scalar_t__ cx; } ;
typedef  TYPE_1__ SIZEL ;
typedef  TYPE_2__* LPCRECT ;
typedef  int /*<<< orphan*/  IOleInPlaceObject ;
typedef  TYPE_3__ IOCS ;

/* Variables and functions */
 int /*<<< orphan*/  AtlPixelToHiMetric (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 int /*<<< orphan*/  IID_IOleInPlaceObject ; 
 int /*<<< orphan*/  IOleInPlaceObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleInPlaceObject_SetObjectRects (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  IOleObject_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleObject_SetExtent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void IOCS_OnSize( IOCS* This, LPCRECT rect )
{
    SIZEL inPix, inHi;

    This->size = *rect;

    if ( !This->control )
        return;

    inPix.cx = rect->right - rect->left;
    inPix.cy = rect->bottom - rect->top;
    AtlPixelToHiMetric( &inPix, &inHi );
    IOleObject_SetExtent( This->control, DVASPECT_CONTENT, &inHi );

    if ( This->fInPlace )
    {
        IOleInPlaceObject *wl;

        if ( SUCCEEDED( IOleObject_QueryInterface( This->control, &IID_IOleInPlaceObject, (void**)&wl ) ) )
        {
            IOleInPlaceObject_SetObjectRects( wl, rect, rect );
            IOleInPlaceObject_Release( wl );
        }
    }
}