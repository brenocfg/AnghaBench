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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {scalar_t__ pLocalDrvrInst; scalar_t__ hDrvr; } ;
typedef  TYPE_1__* PWINE_ACMDRIVER ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HACMDRIVER ;

/* Variables and functions */
 int /*<<< orphan*/  MMSYSERR_INVALHANDLE ; 
 int /*<<< orphan*/  MSACM_DRIVER_SendMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* MSACM_GetDriver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendDriverMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MMRESULT MSACM_Message(HACMDRIVER had, UINT uMsg, LPARAM lParam1, LPARAM lParam2)
{
    PWINE_ACMDRIVER	pad = MSACM_GetDriver(had);

    if (!pad) return MMSYSERR_INVALHANDLE;
    if (pad->hDrvr) return SendDriverMessage(pad->hDrvr, uMsg, lParam1, lParam2);
    if (pad->pLocalDrvrInst) return MSACM_DRIVER_SendMessage(pad->pLocalDrvrInst, uMsg, lParam1, lParam2);

    return MMSYSERR_INVALHANDLE;
}