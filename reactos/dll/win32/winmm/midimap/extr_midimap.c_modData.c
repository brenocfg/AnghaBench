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
typedef  size_t WORD ;
struct TYPE_6__ {TYPE_1__** ChannelMap; } ;
struct TYPE_5__ {int loaded; int* aChn; int* lpbPatch; int /*<<< orphan*/  hMidi; int /*<<< orphan*/  uDevID; } ;
typedef  TYPE_2__ MIDIMAPDATA ;
typedef  int DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_NULL ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int HIBYTE (int /*<<< orphan*/ ) ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWORD (int) ; 
 scalar_t__ MIDIMAP_IsBadData (TYPE_2__*) ; 
 int /*<<< orphan*/  MMSYSERR_ERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  midiOutOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midiOutShortMsg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static	DWORD	modData(MIDIMAPDATA* mom, DWORD_PTR dwParam)
{
    BYTE	lb = LOBYTE(LOWORD(dwParam));
    WORD	chn = lb & 0x0F;
    DWORD	ret = MMSYSERR_NOERROR;

    if (MIDIMAP_IsBadData(mom))
	return MMSYSERR_ERROR;

    if (!mom->ChannelMap[chn]) return MMSYSERR_NOERROR;

    switch (lb & 0xF0)
    {
    case 0x80:
    case 0x90:
    case 0xA0:
    case 0xB0:
    case 0xC0:
    case 0xD0:
    case 0xE0:
	if (mom->ChannelMap[chn]->loaded == 0)
	{
	    if (midiOutOpen(&mom->ChannelMap[chn]->hMidi, mom->ChannelMap[chn]->uDevID,
			    0L, 0L, CALLBACK_NULL) == MMSYSERR_NOERROR)
		mom->ChannelMap[chn]->loaded = 1;
	    else
		mom->ChannelMap[chn]->loaded = -1;
	    /* FIXME: should load here the IDF midi data... and allow channel and
	     * patch mappings
	     */
	}
	if (mom->ChannelMap[chn]->loaded > 0)
	{
	    /* change channel */
	    dwParam &= ~0x0F;
	    dwParam |= mom->ChannelMap[chn]->aChn[chn];

	    if ((LOBYTE(LOWORD(dwParam)) & 0xF0) == 0xC0 /* program change */ &&
		mom->ChannelMap[chn]->lpbPatch)
	    {
		BYTE patch = HIBYTE(LOWORD(dwParam));

		/* change patch */
		dwParam &= ~0x0000FF00;
		dwParam |= mom->ChannelMap[chn]->lpbPatch[patch];
	    }
	    ret = midiOutShortMsg(mom->ChannelMap[chn]->hMidi, dwParam);
	}
	break;
    case 0xF0:
	for (chn = 0; chn < 16; chn++)
	{
	    if (mom->ChannelMap[chn]->loaded > 0)
		ret = midiOutShortMsg(mom->ChannelMap[chn]->hMidi, dwParam);
	}
	break;
    default:
	FIXME("ooch %lu\n", dwParam);
    }

    return ret;
}