#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINE_ACMDRIVERID ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {TYPE_2__* pACMDriverID; int /*<<< orphan*/  dwType; } ;
struct TYPE_12__ {int /*<<< orphan*/  fdwSupport; struct TYPE_12__* pszDriverAlias; struct TYPE_12__* pNextACMDriverID; struct TYPE_12__* pPrevACMDriverID; int /*<<< orphan*/ * pACMDriverList; scalar_t__ pLocalDriver; struct TYPE_12__* pszFileName; TYPE_1__ obj; } ;
typedef  scalar_t__ PWINE_ACMLOCALDRIVER ;
typedef  TYPE_2__* PWINE_ACMDRIVERID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_LOCAL ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MSACM_FillCache (TYPE_2__*) ; 
 int /*<<< orphan*/  MSACM_ReadCache (TYPE_2__*) ; 
 int /*<<< orphan*/  MSACM_UnregisterDriver (TYPE_2__*) ; 
 int /*<<< orphan*/  MSACM_hHeap ; 
 TYPE_2__* MSACM_pFirstACMDriverID ; 
 TYPE_2__* MSACM_pLastACMDriverID ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_ACMOBJ_DRIVERID ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 

PWINE_ACMDRIVERID MSACM_RegisterDriver(LPCWSTR pszDriverAlias, LPCWSTR pszFileName,
				       PWINE_ACMLOCALDRIVER pLocalDriver)
{
    PWINE_ACMDRIVERID	padid;

    TRACE("(%s, %s, %p)\n", 
          debugstr_w(pszDriverAlias), debugstr_w(pszFileName), pLocalDriver);

    padid = HeapAlloc(MSACM_hHeap, 0, sizeof(WINE_ACMDRIVERID));
    if (!padid)
        return NULL;
    padid->obj.dwType = WINE_ACMOBJ_DRIVERID;
    padid->obj.pACMDriverID = padid;
    padid->pszDriverAlias = NULL;
    if (pszDriverAlias)
    {
        padid->pszDriverAlias = HeapAlloc( MSACM_hHeap, 0, (lstrlenW(pszDriverAlias)+1) * sizeof(WCHAR) );
        if (!padid->pszDriverAlias) {
            HeapFree(MSACM_hHeap, 0, padid);
            return NULL;
        }
        lstrcpyW( padid->pszDriverAlias, pszDriverAlias );
    }
    padid->pszFileName = NULL;
    if (pszFileName)
    {
        padid->pszFileName = HeapAlloc( MSACM_hHeap, 0, (lstrlenW(pszFileName)+1) * sizeof(WCHAR) );
        if (!padid->pszFileName) {
            HeapFree(MSACM_hHeap, 0, padid->pszDriverAlias);
            HeapFree(MSACM_hHeap, 0, padid);
            return NULL;
        }
        lstrcpyW( padid->pszFileName, pszFileName );
    }
    padid->pLocalDriver = pLocalDriver;

    padid->pACMDriverList = NULL;
    
    if (pLocalDriver) {
        padid->pPrevACMDriverID = NULL;
        padid->pNextACMDriverID = MSACM_pFirstACMDriverID;
        if (MSACM_pFirstACMDriverID)
            MSACM_pFirstACMDriverID->pPrevACMDriverID = padid;
        MSACM_pFirstACMDriverID = padid;
        if (!MSACM_pLastACMDriverID)
            MSACM_pLastACMDriverID = padid;
    } else {
        padid->pNextACMDriverID = NULL;
        padid->pPrevACMDriverID = MSACM_pLastACMDriverID;
        if (MSACM_pLastACMDriverID)
	    MSACM_pLastACMDriverID->pNextACMDriverID = padid;
        MSACM_pLastACMDriverID = padid;
        if (!MSACM_pFirstACMDriverID)
	    MSACM_pFirstACMDriverID = padid;
    }
    /* disable the driver if we cannot load the cache */
    if ((!padid->pszDriverAlias || !MSACM_ReadCache(padid)) && !MSACM_FillCache(padid)) {
	WARN("Couldn't load cache for ACM driver (%s)\n", debugstr_w(pszFileName));
	MSACM_UnregisterDriver(padid);
	return NULL;
    }

    if (pLocalDriver) padid->fdwSupport |= ACMDRIVERDETAILS_SUPPORTF_LOCAL;
    return padid;
}