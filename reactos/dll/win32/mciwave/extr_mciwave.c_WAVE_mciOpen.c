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
struct TYPE_7__ {scalar_t__ nUseCount; scalar_t__ hFile; int /*<<< orphan*/ * lpFileName; int /*<<< orphan*/  dwStatus; scalar_t__ dwPosition; int /*<<< orphan*/  wNotifyDeviceID; int /*<<< orphan*/ * hCallback; scalar_t__ hWave; int /*<<< orphan*/  fInput; int /*<<< orphan*/  wOutput; int /*<<< orphan*/  wInput; } ;
typedef  TYPE_1__ WINE_MCIWAVE ;
struct TYPE_8__ {int /*<<< orphan*/  dwCallback; int /*<<< orphan*/  lpstrElementName; int /*<<< orphan*/  wDeviceID; } ;
typedef  int /*<<< orphan*/  MCIDEVICEID ;
typedef  int LRESULT ;
typedef  TYPE_2__* LPMCI_WAVE_OPEN_PARMSW ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MCIERR_DEVICE_OPEN ; 
 int MCIERR_INVALID_DEVICE_ID ; 
 int MCIERR_NULL_PARAMETER_BLOCK ; 
 int MCIERR_UNRECOGNIZED_COMMAND ; 
 int MCIERR_UNSUPPORTED_FUNCTION ; 
 int /*<<< orphan*/  MCI_MODE_NOT_READY ; 
 int /*<<< orphan*/  MCI_MODE_STOP ; 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int MCI_OPEN_ELEMENT ; 
 int MCI_OPEN_ELEMENT_ID ; 
 int MCI_OPEN_SHAREABLE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  WAVE_MAPPER ; 
 int /*<<< orphan*/  WAVE_mciDefaultFmt (TYPE_1__*) ; 
 int /*<<< orphan*/  WAVE_mciNotify (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int WAVE_mciOpenFile (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mciGetDriverData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmioClose (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT WAVE_mciOpen(MCIDEVICEID wDevID, DWORD dwFlags, LPMCI_WAVE_OPEN_PARMSW lpOpenParms)
{
    DWORD		dwRet = 0;
    WINE_MCIWAVE*	wmw = (WINE_MCIWAVE*)mciGetDriverData(wDevID);

    TRACE("(%04X, %08X, %p)\n", wDevID, dwFlags, lpOpenParms);
    if (lpOpenParms == NULL)	return MCIERR_NULL_PARAMETER_BLOCK;
    if (wmw == NULL) 		return MCIERR_INVALID_DEVICE_ID;

    if (dwFlags & MCI_OPEN_SHAREABLE)
	return MCIERR_UNSUPPORTED_FUNCTION;

    if (wmw->nUseCount > 0) {
	/* The driver is already opened on this channel
	 * Wave driver cannot be shared
	 */
	return MCIERR_DEVICE_OPEN;
    }

    wmw->nUseCount++;

    wmw->wInput = wmw->wOutput = WAVE_MAPPER;
    wmw->fInput = FALSE;
    wmw->hWave = 0;
    wmw->dwStatus = MCI_MODE_NOT_READY;
    wmw->hFile = 0;
    wmw->lpFileName = NULL; /* will be set by WAVE_mciOpenFile */
    wmw->hCallback = NULL;
    WAVE_mciDefaultFmt(wmw);

    TRACE("wDevID=%04X (lpParams->wDeviceID=%08X)\n", wDevID, lpOpenParms->wDeviceID);
    /* Logs show the native winmm calls us with 0 still in lpOpenParms.wDeviceID */
    wmw->wNotifyDeviceID = wDevID;

    if (dwFlags & MCI_OPEN_ELEMENT) {
	if (dwFlags & MCI_OPEN_ELEMENT_ID) {
	    /* could it be that (DWORD)lpOpenParms->lpstrElementName
	     * contains the hFile value ?
	     */
	    dwRet = MCIERR_UNRECOGNIZED_COMMAND;
	} else {
            dwRet = WAVE_mciOpenFile(wmw, lpOpenParms->lpstrElementName);
	}
    }
    TRACE("hFile=%p\n", wmw->hFile);

    if (dwRet == 0) {
	wmw->dwPosition = 0;

	wmw->dwStatus = MCI_MODE_STOP;

	if (dwFlags & MCI_NOTIFY)
	    WAVE_mciNotify(lpOpenParms->dwCallback, wmw, MCI_NOTIFY_SUCCESSFUL);
    } else {
	wmw->nUseCount--;
	if (wmw->hFile != 0)
	    mmioClose(wmw->hFile, 0);
	wmw->hFile = 0;
	HeapFree(GetProcessHeap(), 0, wmw->lpFileName);
	wmw->lpFileName = NULL;
    }
    return dwRet;
}