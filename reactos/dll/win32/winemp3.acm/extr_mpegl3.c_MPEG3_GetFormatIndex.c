#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nChannels; scalar_t__ rate; scalar_t__ nBits; } ;
struct TYPE_6__ {int wFormatTag; scalar_t__ nChannels; scalar_t__ nSamplesPerSec; scalar_t__ wBitsPerSample; } ;
typedef  TYPE_1__* LPWAVEFORMATEX ;
typedef  TYPE_2__ Format ;
typedef  int DWORD ;

/* Variables and functions */
 TYPE_2__* MPEG3_Formats ; 
 int NUM_MPEG3_FORMATS ; 
 int NUM_PCM_FORMATS ; 
 TYPE_2__* PCM_Formats ; 
#define  WAVE_FORMAT_MPEG 130 
#define  WAVE_FORMAT_MPEGLAYER3 129 
#define  WAVE_FORMAT_PCM 128 

__attribute__((used)) static	DWORD	MPEG3_GetFormatIndex(LPWAVEFORMATEX wfx)
{
    int 	i, hi;
    const Format *fmts;

    switch (wfx->wFormatTag)
    {
    case WAVE_FORMAT_PCM:
	hi = NUM_PCM_FORMATS;
	fmts = PCM_Formats;
	break;
    case WAVE_FORMAT_MPEG:
    case WAVE_FORMAT_MPEGLAYER3:
	hi = NUM_MPEG3_FORMATS;
	fmts = MPEG3_Formats;
	break;
    default:
	return 0xFFFFFFFF;
    }

    for (i = 0; i < hi; i++)
    {
	if (wfx->nChannels == fmts[i].nChannels &&
	    wfx->nSamplesPerSec == fmts[i].rate &&
	    (wfx->wBitsPerSample == fmts[i].nBits || !fmts[i].nBits))
	    return i;
    }

    return 0xFFFFFFFF;
}