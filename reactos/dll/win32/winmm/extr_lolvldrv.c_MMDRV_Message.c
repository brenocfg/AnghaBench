#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nIDMin; int nIDMax; int /*<<< orphan*/  (* fnMessage32 ) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ WINE_MM_DRIVER_PART ;
struct TYPE_9__ {int wMaxId; int /*<<< orphan*/  typestr; int /*<<< orphan*/  bSupportMapper; } ;
typedef  TYPE_2__ WINE_LLTYPE ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {size_t type; int uDeviceID; size_t mmdIndex; int /*<<< orphan*/  dwDriverInstance; } ;
struct TYPE_10__ {TYPE_1__* parts; } ;
typedef  TYPE_3__* LPWINE_MM_DRIVER ;
typedef  TYPE_4__* LPWINE_MLD ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int,int) ; 
 TYPE_3__* MMDrvs ; 
 int /*<<< orphan*/  MMSYSERR_BADDEVICEID ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  WARN (char*,int,...) ; 
 int /*<<< orphan*/  WINMM_ErrorToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  (*) (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 TYPE_2__* llTypes ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DWORD  MMDRV_Message(LPWINE_MLD mld, UINT wMsg, DWORD_PTR dwParam1,
                     DWORD_PTR dwParam2)
{
    LPWINE_MM_DRIVER 		lpDrv;
    DWORD			ret;
    WINE_MM_DRIVER_PART*	part;
    WINE_LLTYPE*		llType = &llTypes[mld->type];
    int				devID;

    TRACE("(%s %u %u 0x%08lx 0x%08lx 0x%08lx)\n",
	  llTypes[mld->type].typestr, mld->uDeviceID, wMsg,
	  mld->dwDriverInstance, dwParam1, dwParam2);

    if (mld->uDeviceID == (UINT16)-1) {
	if (!llType->bSupportMapper) {
	    WARN("uDev=-1 requested on non-mappable ll type %s\n",
		 llTypes[mld->type].typestr);
	    return MMSYSERR_BADDEVICEID;
	}
	devID = -1;
    } else {
	if (mld->uDeviceID >= llType->wMaxId) {
	    WARN("uDev(%u) requested >= max (%d)\n", mld->uDeviceID, llType->wMaxId);
	    return MMSYSERR_BADDEVICEID;
	}
	devID = mld->uDeviceID;
    }

    lpDrv = &MMDrvs[mld->mmdIndex];
    part = &lpDrv->parts[mld->type];

#if 0
    /* some sanity checks */
    if (!(part->nIDMin <= devID))
	ERR("!(part->nIDMin(%d) <= devID(%d))\n", part->nIDMin, devID);
    if (!(devID < part->nIDMax))
	ERR("!(devID(%d) < part->nIDMax(%d))\n", devID, part->nIDMax);
#endif

    assert(part->fnMessage32);

    TRACE("Calling message(dev=%u msg=%u usr=0x%08lx p1=0x%08lx p2=0x%08lx)\n",
          mld->uDeviceID, wMsg, mld->dwDriverInstance, dwParam1, dwParam2);
    ret = part->fnMessage32(mld->uDeviceID, wMsg, mld->dwDriverInstance, dwParam1, dwParam2);
    TRACE("=> %s\n", WINMM_ErrorToString(ret));

    return ret;
}