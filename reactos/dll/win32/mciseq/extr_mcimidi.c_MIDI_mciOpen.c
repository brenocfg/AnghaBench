#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ nUseCount; scalar_t__ hFile; int nDivision; int /*<<< orphan*/  dwStatus; scalar_t__ dwPositionMS; int /*<<< orphan*/ * lpstrName; int /*<<< orphan*/ * lpstrCopyright; int /*<<< orphan*/ * lpstrElementName; int /*<<< orphan*/ * tracks; scalar_t__ wFormat; scalar_t__ nTracks; int /*<<< orphan*/  dwMciTimeFormat; int /*<<< orphan*/  wDevID; int /*<<< orphan*/  wPort; scalar_t__ hMidi; } ;
typedef  TYPE_1__ WINE_MCIMIDI ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int /*<<< orphan*/  dwCallback; scalar_t__* lpstrElementName; int /*<<< orphan*/  wDeviceID; } ;
struct TYPE_11__ {scalar_t__ ckid; scalar_t__ fccType; int cksize; int dwDataOffset; } ;
typedef  TYPE_2__ MMCKINFO ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  TYPE_3__* LPMCI_OPEN_PARMSW ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ FOURCC_RIFF ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MCIERR_DEVICE_OPEN ; 
 int MCIERR_FILE_NOT_FOUND ; 
 int MCIERR_HARDWARE ; 
 int MCIERR_INVALID_FILE ; 
 int MCIERR_NULL_PARAMETER_BLOCK ; 
 int /*<<< orphan*/  MCI_FORMAT_MILLISECONDS ; 
 int /*<<< orphan*/  MCI_MODE_NOT_READY ; 
 int /*<<< orphan*/  MCI_MODE_STOP ; 
 int MCI_NOTIFY ; 
 int /*<<< orphan*/  MCI_NOTIFY_SUCCESSFUL ; 
 int MCI_OPEN_ELEMENT ; 
 int MCI_OPEN_SHAREABLE ; 
 int /*<<< orphan*/  MIDI_MAPPER ; 
 int /*<<< orphan*/  MIDI_mciNotify (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MIDI_mciReadMThd (TYPE_1__*,int) ; 
 int MMIO_ALLOCBUF ; 
 int MMIO_DENYWRITE ; 
 int /*<<< orphan*/  MMIO_FINDCHUNK ; 
 int MMIO_READ ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,scalar_t__*) ; 
 int lstrlenW (scalar_t__*) ; 
 int /*<<< orphan*/  mmioClose (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioDescend (scalar_t__,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioFOURCC (char,char,char,char) ; 
 scalar_t__ mmioOpenW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmioSeek (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD MIDI_mciOpen(WINE_MCIMIDI* wmm, DWORD dwFlags, LPMCI_OPEN_PARMSW lpParms)
{
    DWORD		dwRet = 0;

    TRACE("(%d, %08X, %p)\n", wmm->wDevID, dwFlags, lpParms);

    if (lpParms == NULL) 	return MCIERR_NULL_PARAMETER_BLOCK;
    if (dwFlags & MCI_OPEN_SHAREABLE)
	return MCIERR_HARDWARE;

    if (wmm->nUseCount > 0) {
	/* The driver is already opened on this channel
	 * MIDI sequencer cannot be shared
	 */
	return MCIERR_DEVICE_OPEN;
    }
    wmm->nUseCount++;

    wmm->hFile = 0;
    wmm->hMidi = 0;
    wmm->wPort = MIDI_MAPPER;
    wmm->lpstrElementName = NULL;

    TRACE("wDevID=%d (lpParams->wDeviceID=%d)\n", wmm->wDevID, lpParms->wDeviceID);
    /*	lpParms->wDeviceID = wDevID;*/

    if (dwFlags & MCI_OPEN_ELEMENT) {
	TRACE("MCI_OPEN_ELEMENT %s!\n", debugstr_w(lpParms->lpstrElementName));
        if (lpParms->lpstrElementName && lpParms->lpstrElementName[0]) {
	    wmm->hFile = mmioOpenW((LPWSTR)lpParms->lpstrElementName, NULL,
				   MMIO_ALLOCBUF | MMIO_READ | MMIO_DENYWRITE);
	    if (wmm->hFile == 0) {
		WARN("Can't find file %s!\n", debugstr_w(lpParms->lpstrElementName));
		wmm->nUseCount--;
		return MCIERR_FILE_NOT_FOUND;
	    }
            wmm->lpstrElementName = HeapAlloc(GetProcessHeap(), 0, 
                                              (lstrlenW(lpParms->lpstrElementName) + 1) * sizeof(WCHAR));
            lstrcpyW(wmm->lpstrElementName, lpParms->lpstrElementName);
	}
    }
    TRACE("hFile=%p\n", wmm->hFile);

    wmm->lpstrCopyright = NULL;
    wmm->lpstrName = NULL;

    wmm->dwStatus = MCI_MODE_NOT_READY;	/* while loading file contents */
    /* spec says it should be the default format from the MIDI file... */
    wmm->dwMciTimeFormat = MCI_FORMAT_MILLISECONDS;

    if (wmm->hFile != 0) {
	MMCKINFO	ckMainRIFF;
	MMCKINFO	mmckInfo;
	DWORD		dwOffset = 0;

	if (mmioDescend(wmm->hFile, &ckMainRIFF, NULL, 0) != 0) {
	    dwRet = MCIERR_INVALID_FILE;
	} else {
	    TRACE("ParentChunk ckid=%.4s fccType=%.4s cksize=%08X\n",
		  (LPSTR)&ckMainRIFF.ckid, (LPSTR)&ckMainRIFF.fccType, ckMainRIFF.cksize);

	    if (ckMainRIFF.ckid == FOURCC_RIFF && ckMainRIFF.fccType == mmioFOURCC('R', 'M', 'I', 'D')) {
		mmckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioSeek(wmm->hFile, ckMainRIFF.dwDataOffset + ((ckMainRIFF.cksize + 1) & ~1), SEEK_SET);
		if (mmioDescend(wmm->hFile, &mmckInfo, &ckMainRIFF, MMIO_FINDCHUNK) == 0) {
		    TRACE("... is a 'RMID' file\n");
		    dwOffset = mmckInfo.dwDataOffset;
		} else {
		    dwRet = MCIERR_INVALID_FILE;
		}
	    }
	    if (dwRet == 0 && MIDI_mciReadMThd(wmm, dwOffset) != 0) {
		WARN("Can't read 'MThd' header\n");
		dwRet = MCIERR_INVALID_FILE;
	    }
	}
    } else {
	TRACE("hFile==0, setting #tracks to 0; is this correct ?\n");
	wmm->nTracks = 0;
	wmm->wFormat = 0;
	wmm->nDivision = 1;
    }
    if (dwRet != 0) {
	wmm->nUseCount--;
	if (wmm->hFile != 0)
	    mmioClose(wmm->hFile, 0);
	wmm->hFile = 0;
	HeapFree(GetProcessHeap(), 0, wmm->tracks);
	HeapFree(GetProcessHeap(), 0, wmm->lpstrElementName);
	HeapFree(GetProcessHeap(), 0, wmm->lpstrCopyright);
	HeapFree(GetProcessHeap(), 0, wmm->lpstrName);
    } else {
	wmm->dwPositionMS = 0;
	wmm->dwStatus = MCI_MODE_STOP;
	if (dwFlags & MCI_NOTIFY)
	    MIDI_mciNotify(lpParms->dwCallback, wmm, MCI_NOTIFY_SUCCESSFUL);
    }
    return dwRet;
}