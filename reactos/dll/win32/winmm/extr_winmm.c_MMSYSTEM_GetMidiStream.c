#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINE_MIDIStream ;
struct TYPE_6__ {scalar_t__ dwStreamID; } ;
struct TYPE_7__ {TYPE_1__ rgIds; } ;
struct TYPE_8__ {TYPE_2__ mod; } ;
typedef  TYPE_3__ WINE_MIDI ;
typedef  scalar_t__ ULONG_PTR ;
typedef  TYPE_3__* LPWINE_MIDI ;
typedef  int /*<<< orphan*/  HMIDISTRM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MMDRV_Get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMDRV_MIDIOUT ; 

__attribute__((used)) static	BOOL	MMSYSTEM_GetMidiStream(HMIDISTRM hMidiStrm, WINE_MIDIStream** lpMidiStrm, WINE_MIDI** lplpwm)
{
    WINE_MIDI* lpwm = (LPWINE_MIDI)MMDRV_Get(hMidiStrm, MMDRV_MIDIOUT, FALSE);

    if (lplpwm)
	*lplpwm = lpwm;

    if (lpwm == NULL) {
	return FALSE;
    }

    *lpMidiStrm = (WINE_MIDIStream*)(ULONG_PTR)lpwm->mod.rgIds.dwStreamID; // FIXME: not 64 bit safe

    return *lpMidiStrm != NULL;
}