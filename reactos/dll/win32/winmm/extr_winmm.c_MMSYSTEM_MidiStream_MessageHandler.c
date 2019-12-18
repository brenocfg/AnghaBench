#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_5__* lpMidiHdr; int /*<<< orphan*/  hDevice; int /*<<< orphan*/  wFlags; int /*<<< orphan*/  dwStartTicks; int /*<<< orphan*/  hEvent; } ;
typedef  TYPE_2__ WINE_MIDIStream ;
struct TYPE_15__ {int dwStreamID; } ;
struct TYPE_14__ {int dwFlags; int dwBufferLength; int /*<<< orphan*/  dwOffset; struct TYPE_14__* lpNext; int /*<<< orphan*/  dwBytesRecorded; int /*<<< orphan*/  lpData; } ;
struct TYPE_13__ {int message; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; } ;
struct TYPE_10__ {int /*<<< orphan*/  dwInstance; int /*<<< orphan*/  dwCallback; } ;
struct TYPE_12__ {TYPE_1__ mod; } ;
typedef  TYPE_3__* LPWINE_MIDI ;
typedef  TYPE_4__* LPMSG ;
typedef  TYPE_5__* LPMIDIHDR ;
typedef  TYPE_6__* LPMIDIEVENT ;
typedef  int* LPBYTE ;
typedef  int /*<<< orphan*/  HDRVR ;
typedef  int DWORD_PTR ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DriverCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GetTickCount () ; 
 int MHDR_DONE ; 
 int MHDR_INQUEUE ; 
 int MHDR_ISSTRM ; 
 int /*<<< orphan*/  MM_MOM_DONE ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
#define  WINE_MSM_HEADER 130 
#define  WINE_MSM_STOP 129 
#define  WM_QUIT 128 
 int dwToGo ; 
 int /*<<< orphan*/  midiOutReset (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static	BOOL	MMSYSTEM_MidiStream_MessageHandler(WINE_MIDIStream* lpMidiStrm, LPWINE_MIDI lpwm, LPMSG msg)
{
    LPMIDIHDR	lpMidiHdr;
    LPMIDIHDR*	lpmh;
    LPBYTE	lpData;

    switch (msg->message) {
    case WM_QUIT:
	SetEvent(lpMidiStrm->hEvent);
	return FALSE;
    case WINE_MSM_STOP:
	TRACE("STOP\n");
	/* this is not quite what MS doc says... */
	midiOutReset(lpMidiStrm->hDevice);
	/* empty list of already submitted buffers */
	for (lpMidiHdr = lpMidiStrm->lpMidiHdr; lpMidiHdr; lpMidiHdr = lpMidiHdr->lpNext) {
	    lpMidiHdr->dwFlags |= MHDR_DONE;
	    lpMidiHdr->dwFlags &= ~MHDR_INQUEUE;

	    DriverCallback(lpwm->mod.dwCallback, lpMidiStrm->wFlags,
			   (HDRVR)lpMidiStrm->hDevice, MM_MOM_DONE,
			   lpwm->mod.dwInstance, (DWORD_PTR)lpMidiHdr, 0);
	}
	lpMidiStrm->lpMidiHdr = 0;
	SetEvent(lpMidiStrm->hEvent);
	break;
    case WINE_MSM_HEADER:
	/* sets initial tick count for first MIDIHDR */
	if (!lpMidiStrm->dwStartTicks)
	    lpMidiStrm->dwStartTicks = GetTickCount();

	/* FIXME(EPP): "I don't understand the content of the first MIDIHDR sent
	 * by native mcimidi, it doesn't look like a correct one".
	 * this trick allows to throw it away... but I don't like it.
	 * It looks like part of the file I'm trying to play and definitively looks
	 * like raw midi content
	 * I'd really like to understand why native mcimidi sends it. Perhaps a bad
	 * synchronization issue where native mcimidi is still processing raw MIDI
	 * content before generating MIDIEVENTs ?
	 *
	 * 4c 04 89 3b 00 81 7c 99 3b 43 00 99 23 5e 04 89 L..;..|.;C..#^..
	 * 3b 00 00 89 23 00 7c 99 3b 45 00 99 28 62 04 89 ;...#.|.;E..(b..
	 * 3b 00 00 89 28 00 81 7c 99 3b 4e 00 99 23 5e 04 ;...(..|.;N..#^.
	 * 89 3b 00 00 89 23 00 7c 99 3b 45 00 99 23 78 04 .;...#.|.;E..#x.
	 * 89 3b 00 00 89 23 00 81 7c 99 3b 48 00 99 23 5e .;...#..|.;H..#^
	 * 04 89 3b 00 00 89 23 00 7c 99 3b 4e 00 99 28 62 ..;...#.|.;N..(b
	 * 04 89 3b 00 00 89 28 00 81 7c 99 39 4c 00 99 23 ..;...(..|.9L..#
	 * 5e 04 89 39 00 00 89 23 00 82 7c 99 3b 4c 00 99 ^..9...#..|.;L..
	 * 23 5e 04 89 3b 00 00 89 23 00 7c 99 3b 48 00 99 #^..;...#.|.;H..
	 * 28 62 04 89 3b 00 00 89 28 00 81 7c 99 3b 3f 04 (b..;...(..|.;?.
	 * 89 3b 00 1c 99 23 5e 04 89 23 00 5c 99 3b 45 00 .;...#^..#.\.;E.
	 * 99 23 78 04 89 3b 00 00 89 23 00 81 7c 99 3b 46 .#x..;...#..|.;F
	 * 00 99 23 5e 04 89 3b 00 00 89 23 00 7c 99 3b 48 ..#^..;...#.|.;H
	 * 00 99 28 62 04 89 3b 00 00 89 28 00 81 7c 99 3b ..(b..;...(..|.;
	 * 46 00 99 23 5e 04 89 3b 00 00 89 23 00 7c 99 3b F..#^..;...#.|.;
	 * 48 00 99 23 78 04 89 3b 00 00 89 23 00 81 7c 99 H..#x..;...#..|.
	 * 3b 4c 00 99 23 5e 04 89 3b 00 00 89 23 00 7c 99 ;L..#^..;...#.|.
	 */
	lpMidiHdr = (LPMIDIHDR)msg->lParam;
	lpData = (LPBYTE)lpMidiHdr->lpData;
	TRACE("Adding %s lpMidiHdr=%p [lpData=0x%p dwBufferLength=%u/%u dwFlags=0x%08x size=%lu]\n",
	      (lpMidiHdr->dwFlags & MHDR_ISSTRM) ? "stream" : "regular", lpMidiHdr,
	      lpMidiHdr, lpMidiHdr->dwBufferLength, lpMidiHdr->dwBytesRecorded,
	      lpMidiHdr->dwFlags, msg->wParam);
#if 0
	/* dumps content of lpMidiHdr->lpData
	 * FIXME: there should be a debug routine somewhere that already does this
	 * I hate spreading this type of shit all around the code
	 */
	for (dwToGo = 0; dwToGo < lpMidiHdr->dwBufferLength; dwToGo += 16) {
	    DWORD	i;
	    BYTE	ch;

	    for (i = 0; i < min(16, lpMidiHdr->dwBufferLength - dwToGo); i++)
		printf("%02x ", lpData[dwToGo + i]);
	    for (; i < 16; i++)
		printf("   ");
	    for (i = 0; i < min(16, lpMidiHdr->dwBufferLength - dwToGo); i++) {
		ch = lpData[dwToGo + i];
		printf("%c", (ch >= 0x20 && ch <= 0x7F) ? ch : '.');
	    }
	    printf("\n");
	}
#endif
	if (((LPMIDIEVENT)lpData)->dwStreamID != 0 &&
	    ((LPMIDIEVENT)lpData)->dwStreamID != 0xFFFFFFFF &&
	    /* FIXME: not 64 bit safe */
	    ((LPMIDIEVENT)lpData)->dwStreamID != (DWORD_PTR)lpMidiStrm) {
	    FIXME("Dropping bad %s lpMidiHdr (streamID=%08x)\n",
		  (lpMidiHdr->dwFlags & MHDR_ISSTRM) ? "stream" : "regular",
		  ((LPMIDIEVENT)lpData)->dwStreamID);
	    lpMidiHdr->dwFlags |= MHDR_DONE;
	    lpMidiHdr->dwFlags &= ~MHDR_INQUEUE;

	    DriverCallback(lpwm->mod.dwCallback, lpMidiStrm->wFlags,
			   (HDRVR)lpMidiStrm->hDevice, MM_MOM_DONE,
			   lpwm->mod.dwInstance, (DWORD_PTR)lpMidiHdr, 0);
	    break;
	}

	for (lpmh = &lpMidiStrm->lpMidiHdr; *lpmh; lpmh = &(*lpmh)->lpNext);
	*lpmh = lpMidiHdr;
	lpMidiHdr = (LPMIDIHDR)msg->lParam;
	lpMidiHdr->lpNext = 0;
	lpMidiHdr->dwFlags |= MHDR_INQUEUE;
	lpMidiHdr->dwFlags &= ~MHDR_DONE;
	lpMidiHdr->dwOffset = 0;

	break;
    default:
	FIXME("Unknown message %d\n", msg->message);
	break;
    }
    return TRUE;
}