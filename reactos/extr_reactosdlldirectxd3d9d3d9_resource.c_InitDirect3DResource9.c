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
typedef  enum REF_TYPE { ____Placeholder_REF_TYPE } REF_TYPE ;
struct TYPE_6__ {int /*<<< orphan*/  Pool; int /*<<< orphan*/  BaseObject; } ;
struct TYPE_5__ {int /*<<< orphan*/  lpVtbl; } ;
typedef  TYPE_1__* LPDIRECT3DDEVICE9_INT ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ Direct3DResource9_INT ;
typedef  int /*<<< orphan*/  D3DPOOL ;

/* Variables and functions */
 int /*<<< orphan*/  InitD3D9BaseObject (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void InitDirect3DResource9(Direct3DResource9_INT* pResource, D3DPOOL Pool, LPDIRECT3DDEVICE9_INT pBaseDevice, enum REF_TYPE RefType)
{
    InitD3D9BaseObject(&pResource->BaseObject, RefType, (IUnknown*)&pBaseDevice->lpVtbl);

    pResource->Pool = Pool;
}