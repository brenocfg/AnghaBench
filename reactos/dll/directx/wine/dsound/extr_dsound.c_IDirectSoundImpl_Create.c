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
struct TYPE_3__ {int /*<<< orphan*/ * device; scalar_t__ ref; } ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND8 ;
typedef  TYPE_1__ IDirectSoundImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static HRESULT IDirectSoundImpl_Create(
    LPDIRECTSOUND8 * ppDS)
{
    IDirectSoundImpl* pDS;
    TRACE("(%p)\n",ppDS);

    /* Allocate memory */
    pDS = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(IDirectSoundImpl));
    if (pDS == NULL) {
        WARN("out of memory\n");
        *ppDS = NULL;
        return DSERR_OUTOFMEMORY;
    }

    pDS->ref    = 0;
    pDS->device = NULL;

    *ppDS = (LPDIRECTSOUND8)pDS;

    return DS_OK;
}