#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int WORD ;
struct TYPE_8__ {int /*<<< orphan*/  hFile; int /*<<< orphan*/ * lpstrName; int /*<<< orphan*/ * lpstrCopyright; } ;
typedef  TYPE_1__ WINE_MCIMIDI ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {scalar_t__ dwFirst; scalar_t__ dwLast; scalar_t__ dwIndex; scalar_t__ wEventLength; int wStatus; scalar_t__ dwEventPulse; scalar_t__ dwLength; int /*<<< orphan*/  wTrackNr; int /*<<< orphan*/  dwEventData; } ;
typedef  TYPE_2__ MCI_MIDITRACK ;
typedef  char* HPSTR ;
typedef  scalar_t__ FOURCC ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HIBYTE (int) ; 
 int HIWORD (int /*<<< orphan*/ ) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ MCIERR_INVALID_FILE ; 
 scalar_t__ MIDI_mciReadLong (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ MIDI_mciReadNextEvent (TYPE_1__*,TYPE_2__*) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ debugstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__ mmioFOURCC (char,char,char,char) ; 
 int mmioRead (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ mmioSeek (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD MIDI_mciReadMTrk(WINE_MCIMIDI* wmm, MCI_MIDITRACK* mmt)
{
    DWORD		toberead;
    FOURCC		fourcc;

    if (mmioRead(wmm->hFile, (HPSTR)&fourcc, (long)sizeof(FOURCC)) !=
	(long)sizeof(FOURCC)) {
	return MCIERR_INVALID_FILE;
    }

    if (fourcc != mmioFOURCC('M', 'T', 'r', 'k')) {
	WARN("Can't synchronize on 'MTrk' !\n");
	return MCIERR_INVALID_FILE;
    }

    if (MIDI_mciReadLong(wmm, &toberead) != 0) {
	return MCIERR_INVALID_FILE;
    }
    mmt->dwFirst = mmioSeek(wmm->hFile, 0, SEEK_CUR); /* >= 0 */
    mmt->dwLast = mmt->dwFirst + toberead;

    /* compute # of pulses in this track */
    mmt->dwIndex = mmt->dwFirst;
    mmt->dwEventPulse = 0;

    while (MIDI_mciReadNextEvent(wmm, mmt) == 0 && LOWORD(mmt->dwEventData) != 0x2FFF) {
	char	buf[1024];
	WORD	len;

	mmt->dwIndex += mmt->wEventLength;

	switch (LOWORD(mmt->dwEventData)) {
	case 0x02FF:
	case 0x03FF:
	    len = mmt->wEventLength - HIWORD(mmt->dwEventData);
	    if (len >= sizeof(buf)) {
		WARN("Buffer for text is too small (%u are needed)\n", len);
		len = sizeof(buf) - 1;
	    }
            if (mmioRead(wmm->hFile, buf, len) == len) {
		buf[len] = 0;	/* end string in case */
		switch (HIBYTE(LOWORD(mmt->dwEventData))) {
		case 0x02:
		    if (wmm->lpstrCopyright) {
			WARN("Two copyright notices (%s|%s)\n", debugstr_w(wmm->lpstrCopyright), buf);
			HeapFree(GetProcessHeap(), 0, wmm->lpstrCopyright);
		    }
		    len = MultiByteToWideChar( CP_ACP, 0, buf, -1, NULL, 0 );
		    wmm->lpstrCopyright = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) );
		    MultiByteToWideChar( CP_ACP, 0, buf, -1, wmm->lpstrCopyright, len );
		    break;
		case 0x03:
		    if (wmm->lpstrName) {
			WARN("Two names (%s|%s)\n", debugstr_w(wmm->lpstrName), buf);
			HeapFree(GetProcessHeap(), 0, wmm->lpstrName);
		    } /* last name or name from last track wins */
		    len = MultiByteToWideChar( CP_ACP, 0, buf, -1, NULL, 0 );
		    wmm->lpstrName = HeapAlloc( GetProcessHeap(), 0, len * sizeof(WCHAR) );
		    MultiByteToWideChar( CP_ACP, 0, buf, -1, wmm->lpstrName, len );
		    break;
		}
	    }
	    break;
	}
    }
    mmt->dwLength = mmt->dwEventPulse;

    TRACE("Track %u has %u bytes and %u pulses\n", mmt->wTrackNr, toberead, mmt->dwLength);

    /* reset track data */
    mmt->wStatus = 1;	/* ok, playing */
    mmt->dwIndex = mmt->dwFirst;
    mmt->dwEventPulse = 0;

    if (mmioSeek(wmm->hFile, 0, SEEK_CUR) != mmt->dwLast) {
	WARN("Ouch, out of sync seek=%u track=%u\n",
	     mmioSeek(wmm->hFile, 0, SEEK_CUR), mmt->dwLast);
	/* position at end of this track, to be ready to read next track */
	mmioSeek(wmm->hFile, mmt->dwLast, SEEK_SET);
    }

    return 0;
}