#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* iks; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; TYPE_2__* dsb; scalar_t__ ref; } ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDBUFFER ;
typedef  TYPE_1__ IKsBufferPropertySetImpl ;
typedef  TYPE_2__ IDirectSoundBufferImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  iksbvt ; 

HRESULT IKsBufferPropertySetImpl_Create(
    IDirectSoundBufferImpl *dsb,
    IKsBufferPropertySetImpl **piks)
{
    IKsBufferPropertySetImpl *iks;
    TRACE("(%p,%p)\n",dsb,piks);
    *piks = NULL;

    iks = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(*iks));
    if (iks == 0) {
        WARN("out of memory\n");
        *piks = NULL;
        return DSERR_OUTOFMEMORY;
    }

    iks->ref = 0;
    iks->dsb = dsb;
    dsb->iks = iks;
    iks->lpVtbl = &iksbvt;

    IDirectSoundBuffer_AddRef((LPDIRECTSOUNDBUFFER)dsb);

    *piks = iks;
    return S_OK;
}