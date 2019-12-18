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
struct TYPE_5__ {int /*<<< orphan*/  (* fnMessage32 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,long) ;} ;
typedef  TYPE_1__ WINE_MM_DRIVER_PART ;
typedef  size_t UINT ;
struct TYPE_6__ {TYPE_1__* parts; } ;
typedef  TYPE_2__* LPWINE_MM_DRIVER ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DRVM_DISABLE ; 
 int /*<<< orphan*/  DRVM_EXIT ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINMM_ErrorToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,long) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,long,long) ; 

__attribute__((used)) static  BOOL	MMDRV_ExitPerType(LPWINE_MM_DRIVER lpDrv, UINT type)
{
    WINE_MM_DRIVER_PART*	part = &lpDrv->parts[type];
    DWORD			ret;
    TRACE("(%p, %04x)\n", lpDrv, type);

    if (part->fnMessage32) {
#if 0
        ret = part->fnMessage32(0, DRVM_DISABLE, 0L, 0L, 0L);
        TRACE("DRVM_DISABLE => %08lx\n", ret);
#endif
        ret = part->fnMessage32(0, DRVM_EXIT, 0L, 0L, 0L);
        TRACE("DRVM_EXIT => %s\n", WINMM_ErrorToString(ret));
    }

    return TRUE;
}