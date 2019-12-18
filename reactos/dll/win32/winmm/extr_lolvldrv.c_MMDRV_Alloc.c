#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT_PTR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {void* dwClientInstance; void* dwCallback; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__* LPWINE_MLD ;
typedef  scalar_t__* LPHANDLE ;
typedef  scalar_t__ HANDLE ;
typedef  void* DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t MAX_MM_MLDRVS ; 
 size_t MMDRV_GetNum (int /*<<< orphan*/ ) ; 
 TYPE_1__** MM_MLDrvs ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,void**,void**) ; 

LPWINE_MLD	MMDRV_Alloc(UINT size, UINT type, LPHANDLE hndl, DWORD* dwFlags,
			    DWORD_PTR* dwCallback, DWORD_PTR* dwInstance)
{
    LPWINE_MLD	mld;
    UINT_PTR i;
    TRACE("(%d, %04x, %p, %p, %p, %p)\n",
          size, type, hndl, dwFlags, dwCallback, dwInstance);

    mld = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    if (!mld)	return NULL;

    /* find an empty slot in MM_MLDrvs table */
    for (i = 0; i < MAX_MM_MLDRVS; i++) if (!MM_MLDrvs[i]) break;

    if (i == MAX_MM_MLDRVS) {
	/* the MM_MLDrvs table could be made growable in the future if needed */
	ERR("Too many open drivers\n");
        HeapFree(GetProcessHeap(), 0, mld);
	return NULL;
    }
    MM_MLDrvs[i] = mld;
    *hndl = (HANDLE)(i | 0x8000);

    mld->type = type;
    if ((UINT_PTR)*hndl < MMDRV_GetNum(type) || ((UINT_PTR)*hndl >> 16)) {
	/* FIXME: those conditions must be fulfilled so that:
	 * - we can distinguish between device IDs and handles
	 * - we can use handles as 16 or 32 bit entities
	 */
	ERR("Shouldn't happen. Bad allocation scheme\n");
    }

    mld->dwFlags = HIWORD(*dwFlags);
    mld->dwCallback = *dwCallback;
    mld->dwClientInstance = *dwInstance;

    return mld;
}