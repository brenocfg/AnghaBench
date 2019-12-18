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
struct TYPE_3__ {int dwFlags; } ;
typedef  int /*<<< orphan*/  MIDIMAPDATA ;
typedef  TYPE_1__* LPMIDIHDR ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int MHDR_ISSTRM ; 
 int MHDR_PREPARED ; 
 scalar_t__ MIDIMAP_IsBadData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMSYSERR_ERROR ; 
 int /*<<< orphan*/  MMSYSERR_INVALPARAM ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 

__attribute__((used)) static	DWORD	modUnprepare(MIDIMAPDATA* mom, LPMIDIHDR lpMidiHdr, DWORD_PTR dwParam2)
{
    if (MIDIMAP_IsBadData(mom)) return MMSYSERR_ERROR;
    if ((lpMidiHdr->dwFlags & MHDR_ISSTRM) || !(lpMidiHdr->dwFlags & MHDR_PREPARED))
	return MMSYSERR_INVALPARAM;

    lpMidiHdr->dwFlags &= ~MHDR_PREPARED;
    return MMSYSERR_NOERROR;
}