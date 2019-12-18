#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_6__ {TYPE_1__** ChannelMap; } ;
struct TYPE_5__ {scalar_t__ loaded; int /*<<< orphan*/  hMidi; } ;
typedef  TYPE_2__ MIDIMAPDATA ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ MIDIMAP_IsBadData (TYPE_2__*) ; 
 scalar_t__ MMSYSERR_ERROR ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ midiOutReset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static	DWORD	modReset(MIDIMAPDATA* mom)
{
    WORD	chn;
    DWORD	ret = MMSYSERR_NOERROR;

    if (MIDIMAP_IsBadData(mom))
	return MMSYSERR_ERROR;

    for (chn = 0; chn < 16; chn++)
    {
	if (mom->ChannelMap[chn] && mom->ChannelMap[chn]->loaded > 0)
	{
	    ret = midiOutReset(mom->ChannelMap[chn]->hMidi);
	    if (ret != MMSYSERR_NOERROR) break;
	}
    }
    return ret;
}