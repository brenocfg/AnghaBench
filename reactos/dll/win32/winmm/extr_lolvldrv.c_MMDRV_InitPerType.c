#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nIDMin; int nIDMax; size_t (* fnMessage32 ) (int /*<<< orphan*/ ,size_t,long,long,long) ;} ;
typedef  TYPE_2__ WINE_MM_DRIVER_PART ;
typedef  int /*<<< orphan*/  WINE_MLD ;
typedef  int UINT16 ;
typedef  size_t UINT ;
struct TYPE_13__ {int uDeviceID; size_t type; size_t mmdIndex; scalar_t__ dwDriverInstance; } ;
struct TYPE_12__ {size_t drvname; TYPE_1__* parts; } ;
struct TYPE_11__ {size_t typestr; int nMapper; int wMaxId; TYPE_7__* lpMlds; } ;
struct TYPE_10__ {int drvname; scalar_t__ bIsMapper; TYPE_2__* parts; } ;
struct TYPE_8__ {int nIDMin; int nIDMax; } ;
typedef  TYPE_3__* LPWINE_MM_DRIVER ;
typedef  void* LPWINE_MLD ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DRVM_ENABLE ; 
 size_t DRVM_INIT ; 
 int /*<<< orphan*/  ERR (char*,size_t,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HIWORD (size_t) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 TYPE_5__* MMDrvs ; 
 int MMDrvsHi ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINMM_ErrorToString (size_t) ; 
 TYPE_4__* llTypes ; 
 size_t stub1 (int /*<<< orphan*/ ,size_t,long,long,long) ; 
 size_t stub2 (int /*<<< orphan*/ ,size_t,long,long,long) ; 
 size_t stub3 (int /*<<< orphan*/ ,size_t,long,long,long) ; 

__attribute__((used)) static  BOOL	MMDRV_InitPerType(LPWINE_MM_DRIVER lpDrv, UINT type, UINT wMsg)
{
    WINE_MM_DRIVER_PART*	part = &lpDrv->parts[type];
    DWORD			ret;
    UINT			count = 0;
    int				i, k;
    TRACE("(%p, %04x, %04x)\n", lpDrv, type, wMsg);

    part->nIDMin = part->nIDMax = 0;

    /* for DRVM_INIT and DRVM_ENABLE, dwParam2 should be PnP node */
    /* the DRVM_ENABLE is only required when the PnP node is non zero */
    if (part->fnMessage32) {
        ret = part->fnMessage32(0, DRVM_INIT, 0L, 0L, 0L);
        TRACE("DRVM_INIT => %s\n", WINMM_ErrorToString(ret));
#if 0
        ret = part->fnMessage32(0, DRVM_ENABLE, 0L, 0L, 0L);
        TRACE("DRVM_ENABLE => %08lx\n", ret);
#endif
        count = part->fnMessage32(0, wMsg, 0L, 0L, 0L);
    }
    else return FALSE;

    TRACE("Got %u dev for (%s:%s)\n", count, lpDrv->drvname, llTypes[type].typestr);
    
    if (HIWORD(count))
        return FALSE;

    /* got some drivers */
    if (lpDrv->bIsMapper) {
	/* it seems native mappers return 0 devices :-( */
	if (llTypes[type].nMapper != -1)
	    ERR("Two mappers for type %s (%d, %s)\n",
		llTypes[type].typestr, llTypes[type].nMapper, lpDrv->drvname);
	if (count > 1)
	    ERR("Strange: mapper with %d > 1 devices\n", count);
	llTypes[type].nMapper = MMDrvsHi;
    } else {
	if (count == 0)
	    return FALSE;
	part->nIDMin = llTypes[type].wMaxId;
	llTypes[type].wMaxId += count;
	part->nIDMax = llTypes[type].wMaxId;
    }
    TRACE("Setting min=%d max=%d (ttop=%d) for (%s:%s)\n",
	  part->nIDMin, part->nIDMax, llTypes[type].wMaxId,
	  lpDrv->drvname, llTypes[type].typestr);
    /* realloc translation table */
    if (llTypes[type].lpMlds)
        llTypes[type].lpMlds = (LPWINE_MLD)
	HeapReAlloc(GetProcessHeap(), 0, llTypes[type].lpMlds - 1,
		    sizeof(WINE_MLD) * (llTypes[type].wMaxId + 1)) + 1;
    else
        llTypes[type].lpMlds = (LPWINE_MLD)
	HeapAlloc(GetProcessHeap(), 0,
		    sizeof(WINE_MLD) * (llTypes[type].wMaxId + 1)) + 1;

    /* re-build the translation table */
    if (llTypes[type].nMapper != -1) {
	TRACE("%s:Trans[%d] -> %s\n", llTypes[type].typestr, -1, MMDrvs[llTypes[type].nMapper].drvname);
	llTypes[type].lpMlds[-1].uDeviceID = (UINT16)-1;
	llTypes[type].lpMlds[-1].type = type;
	llTypes[type].lpMlds[-1].mmdIndex = llTypes[type].nMapper;
	llTypes[type].lpMlds[-1].dwDriverInstance = 0;
    }
    for (i = k = 0; i <= MMDrvsHi; i++) {
	while (MMDrvs[i].parts[type].nIDMin <= k && k < MMDrvs[i].parts[type].nIDMax) {
	    TRACE("%s:Trans[%d] -> %s\n", llTypes[type].typestr, k, MMDrvs[i].drvname);
	    llTypes[type].lpMlds[k].uDeviceID = k;
	    llTypes[type].lpMlds[k].type = type;
	    llTypes[type].lpMlds[k].mmdIndex = i;
	    llTypes[type].lpMlds[k].dwDriverInstance = 0;
	    k++;
	}
    }
    return TRUE;
}