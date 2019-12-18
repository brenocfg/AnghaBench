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
struct TYPE_3__ {int fdwSupport; int /*<<< orphan*/  dwNotifyMsg; int /*<<< orphan*/  hNotifyWnd; struct TYPE_3__* pNextACMNotifyWnd; } ;
typedef  TYPE_1__* PWINE_ACMNOTIFYWND ;

/* Variables and functions */
 int ACMDRIVERDETAILS_SUPPORTF_DISABLED ; 
 TYPE_1__* MSACM_pFirstACMNotifyWnd ; 
 int /*<<< orphan*/  MSACM_pendingBroadcast ; 
 scalar_t__ MSACM_suspendBroadcastCount ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

void MSACM_BroadcastNotification(void)
{
    if (MSACM_suspendBroadcastCount <= 0) {
        PWINE_ACMNOTIFYWND panwnd;

        for (panwnd = MSACM_pFirstACMNotifyWnd; panwnd; panwnd = panwnd->pNextACMNotifyWnd) 
        if (!(panwnd->fdwSupport & ACMDRIVERDETAILS_SUPPORTF_DISABLED))
            SendMessageW(panwnd->hNotifyWnd, panwnd->dwNotifyMsg, 0, 0);
    } else {
        MSACM_pendingBroadcast = TRUE;
    }
}