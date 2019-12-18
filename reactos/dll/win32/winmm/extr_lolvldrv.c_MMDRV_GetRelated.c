#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nIDMin; scalar_t__ nIDMax; } ;
typedef  TYPE_1__ WINE_MM_DRIVER_PART ;
typedef  size_t UINT ;
struct TYPE_9__ {TYPE_1__* parts; } ;
struct TYPE_8__ {size_t mmdIndex; } ;
typedef  TYPE_2__* LPWINE_MLD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 TYPE_2__* MMDRV_Get (int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 TYPE_2__* MMDRV_GetByID (scalar_t__,size_t) ; 
 TYPE_3__* MMDrvs ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,size_t,char,size_t) ; 

LPWINE_MLD	MMDRV_GetRelated(HANDLE hndl, UINT srcType,
				 BOOL bSrcCanBeID, UINT dstType)
{
    LPWINE_MLD		mld;
    TRACE("(%p, %04x, %c, %04x)\n",
          hndl, srcType, bSrcCanBeID ? 'Y' : 'N', dstType);

    if ((mld = MMDRV_Get(hndl, srcType, bSrcCanBeID)) != NULL) {
	WINE_MM_DRIVER_PART*	part = &MMDrvs[mld->mmdIndex].parts[dstType];
	if (part->nIDMin < part->nIDMax)
	    return MMDRV_GetByID(part->nIDMin, dstType);
    }
    return NULL;
}