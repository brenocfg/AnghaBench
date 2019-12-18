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
struct TYPE_3__ {int nDivision; scalar_t__ dwTempo; } ;
typedef  TYPE_1__ WINE_MCIMIDI ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ HIBYTE (int) ; 
 int LOBYTE (int) ; 

__attribute__((used)) static	DWORD	MIDI_ConvertPulseToMS(WINE_MCIMIDI* wmm, DWORD pulse)
{
    DWORD	ret = 0;

    /* FIXME: this function may return false values since the tempo (wmm->dwTempo)
     * may change during file playing
     */
    if (wmm->nDivision == 0) {
	FIXME("Shouldn't happen. wmm->nDivision = 0\n");
    } else if (wmm->nDivision > 0x8000) { /* SMPTE, unchecked FIXME? */
	int	nf = -(char)HIBYTE(wmm->nDivision);	/* number of frames     */
	int	nsf = LOBYTE(wmm->nDivision);		/* number of sub-frames */
	ret = (pulse * 1000) / (nf * nsf);
    } else {
	ret = (DWORD)((double)pulse * ((double)wmm->dwTempo / 1000) /
		      (double)wmm->nDivision);
    }

    /*
      TRACE("pulse=%u tempo=%u division=%u=0x%04x => ms=%u\n",
      pulse, wmm->dwTempo, wmm->nDivision, wmm->nDivision, ret);
    */

    return ret;
}