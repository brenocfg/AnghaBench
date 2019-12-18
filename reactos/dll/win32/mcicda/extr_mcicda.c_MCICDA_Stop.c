#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hThread; scalar_t__ stopEvent; int /*<<< orphan*/  handle; int /*<<< orphan*/ * dsObj; int /*<<< orphan*/ * dsBuf; int /*<<< orphan*/  wNotifyDeviceID; int /*<<< orphan*/  hCallback; } ;
typedef  TYPE_1__ WINE_MCICDAUDIO ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/  dwCallback; } ;
typedef  TYPE_2__* LPMCI_GENERIC_PARMS ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IOCTL_CDROM_STOP_AUDIO ; 
 scalar_t__ InterlockedExchangePointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* MCICDA_GetOpenDrv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCICDA_Notify (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MCIERR_HARDWARE ; 
 int MCIERR_INVALID_DEVICE_ID ; 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_ABORTED ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mciDriverNotify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD MCICDA_Stop(UINT wDevID, DWORD dwFlags, LPMCI_GENERIC_PARMS lpParms)
{
    WINE_MCICDAUDIO*	wmcda = MCICDA_GetOpenDrv(wDevID);
    HANDLE		oldcb;
    DWORD               br;

    TRACE("(%04X, %08X, %p);\n", wDevID, dwFlags, lpParms);

    if (wmcda == NULL)	return MCIERR_INVALID_DEVICE_ID;

    oldcb = InterlockedExchangePointer(&wmcda->hCallback, NULL);
    if (oldcb) mciDriverNotify(oldcb, wmcda->wNotifyDeviceID, MCI_NOTIFY_ABORTED);

    if (wmcda->hThread != 0) {
        SetEvent(wmcda->stopEvent);
        WaitForSingleObject(wmcda->hThread, INFINITE);

        CloseHandle(wmcda->hThread);
        wmcda->hThread = 0;
        CloseHandle(wmcda->stopEvent);
        wmcda->stopEvent = 0;

        IDirectSoundBuffer_Release(wmcda->dsBuf);
        wmcda->dsBuf = NULL;
        IDirectSound_Release(wmcda->dsObj);
        wmcda->dsObj = NULL;
    }
    else if (!device_io(wmcda->handle, IOCTL_CDROM_STOP_AUDIO, NULL, 0, NULL, 0, &br, NULL))
        return MCIERR_HARDWARE;

    if ((dwFlags & MCI_NOTIFY) && lpParms)
	MCICDA_Notify(lpParms->dwCallback, wmcda, MCI_NOTIFY_SUCCESSFUL);
    return 0;
}