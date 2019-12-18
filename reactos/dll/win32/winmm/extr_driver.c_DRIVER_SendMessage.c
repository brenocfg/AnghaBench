#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  dwDriverID; int /*<<< orphan*/  (* lpDrvProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPWINE_DRIVER ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HDRVR ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LRESULT DRIVER_SendMessage(LPWINE_DRIVER lpDrv, UINT msg,
                                         LPARAM lParam1, LPARAM lParam2)
{
    LRESULT		ret = 0;

    TRACE("Before call32 proc=%p drvrID=%08lx hDrv=%p wMsg=%04x p1=%08lx p2=%08lx\n",
          lpDrv->lpDrvProc, lpDrv->dwDriverID, lpDrv, msg, lParam1, lParam2);
    ret = lpDrv->lpDrvProc(lpDrv->dwDriverID, (HDRVR)lpDrv, msg, lParam1, lParam2);
    TRACE("After  call32 proc=%p drvrID=%08lx hDrv=%p wMsg=%04x p1=%08lx p2=%08lx => %08lx\n",
          lpDrv->lpDrvProc, lpDrv->dwDriverID, lpDrv, msg, lParam1, lParam2, ret);

    return ret;
}