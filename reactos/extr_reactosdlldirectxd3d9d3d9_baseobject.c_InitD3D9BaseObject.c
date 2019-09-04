#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum REF_TYPE { ____Placeholder_REF_TYPE } REF_TYPE ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int RefType; int /*<<< orphan*/ * pUnknown; int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ D3D9BaseObject ;

/* Variables and functions */
 int /*<<< orphan*/  D3D9BaseObject_Vtbl ; 

VOID InitD3D9BaseObject(D3D9BaseObject* pBaseObject, enum REF_TYPE RefType, IUnknown* pUnknown)
{
    pBaseObject->lpVtbl = &D3D9BaseObject_Vtbl;
    pBaseObject->RefType = RefType;
    pBaseObject->pUnknown = pUnknown;
}