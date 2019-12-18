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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  lRefCnt; TYPE_2__* pUnknown; } ;
struct TYPE_6__ {TYPE_1__* lpVtbl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* AddRef ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_3__ D3D9BaseObject ;

/* Variables and functions */
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

ULONG D3D9BaseObject_AddRef(D3D9BaseObject* pBaseObject)
{
    if (pBaseObject->pUnknown)
    {
        pBaseObject->pUnknown->lpVtbl->AddRef((IUnknown*) &pBaseObject->pUnknown->lpVtbl);
    }

    return InterlockedIncrement(&pBaseObject->lRefCnt);
}