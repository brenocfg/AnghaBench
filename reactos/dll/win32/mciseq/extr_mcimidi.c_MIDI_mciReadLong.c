#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WINE_MCIMIDI ;
typedef  int /*<<< orphan*/ * LPDWORD ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MCIERR_INVALID_FILE ; 
 scalar_t__ MIDI_mciReadWord (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD MIDI_mciReadLong(WINE_MCIMIDI* wmm, LPDWORD lpdw)
{
    WORD	hiword, loword;
    DWORD	ret = MCIERR_INVALID_FILE;

    if (MIDI_mciReadWord(wmm, &hiword) == 0 &&
	MIDI_mciReadWord(wmm, &loword) == 0) {
	*lpdw = MAKELONG(loword, hiword);
	ret = 0;
    }
    return ret;
}