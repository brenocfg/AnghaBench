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
typedef  int WORD ;
typedef  int /*<<< orphan*/  WINE_MCIMIDI ;
typedef  scalar_t__* LPWORD ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 scalar_t__ MCIERR_INVALID_FILE ; 
 scalar_t__ MIDI_mciReadByte (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static DWORD MIDI_mciReadWord(WINE_MCIMIDI* wmm, LPWORD lpw)
{
    BYTE	hibyte, lobyte;
    DWORD	ret = MCIERR_INVALID_FILE;

    if (MIDI_mciReadByte(wmm, &hibyte) == 0 &&
	MIDI_mciReadByte(wmm, &lobyte) == 0) {
	*lpw = ((WORD)hibyte << 8) + lobyte;
	ret = 0;
    }
    return ret;
}