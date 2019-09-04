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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/ * lpModeInfo; int /*<<< orphan*/ * lpdwFourCC; int /*<<< orphan*/ * lpDDCBtmp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lpLcl; } ;
typedef  TYPE_1__* LPDDRAWI_DIRECTDRAW_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DX_WINDBG_trace () ; 
 int /*<<< orphan*/  DdDeleteDirectDrawObject (TYPE_2__*) ; 
 int /*<<< orphan*/  DxHeapMemFree (int /*<<< orphan*/ *) ; 
 TYPE_2__ ddgbl ; 

VOID
Cleanup(LPDDRAWI_DIRECTDRAW_INT This)
{
    DX_WINDBG_trace();

    if (ddgbl.lpDDCBtmp != NULL)
    {
        DxHeapMemFree(ddgbl.lpDDCBtmp);
    }

    if (ddgbl.lpdwFourCC != NULL)
    {
        DxHeapMemFree(ddgbl.lpdwFourCC);
    }

    if (ddgbl.lpModeInfo != NULL)
    {
        DxHeapMemFree(ddgbl.lpModeInfo);
    }

    DdDeleteDirectDrawObject(&ddgbl);

    /*
       anything else to release?
    */

    /* release the linked interface */
    //while (IsBadWritePtr( This->lpVtbl, sizeof( LPDDRAWI_DIRECTDRAW_INT )) )
    //{
    //    LPDDRAWI_DIRECTDRAW_INT newThis = This->lpVtbl;
    //    if (This->lpLcl != NULL)
    //    {
    //        DeleteDC(This->lpLcl->hDC);
    //        DxHeapMemFree(This->lpLcl);
    //    }

    //    DxHeapMemFree(This);
    //    This = newThis;
    //}

    /* release unlinked interface */
    if (This->lpLcl != NULL)
    {
        DxHeapMemFree(This->lpLcl);
    }
    //if (This != NULL)
    //{
    //    DxHeapMemFree(This);
    //}

}