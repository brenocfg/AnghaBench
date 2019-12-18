#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int wFormatTag; int nChannels; int nSamplesPerSec; int nBlockAlign; int nAvgBytesPerSec; int /*<<< orphan*/  cbSize; int /*<<< orphan*/  wBitsPerSample; } ;
struct TYPE_9__ {int nChannels; int rate; int /*<<< orphan*/  nBits; } ;
struct TYPE_8__ {int dwFormatTag; size_t dwFormatIndex; scalar_t__* szFormat; int /*<<< orphan*/  fdwSupport; TYPE_4__* pwfx; } ;
typedef  TYPE_1__* PACMFORMATDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CODEC ; 
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_FORMATDETAILSF_FORMAT 132 
#define  ACM_FORMATDETAILSF_INDEX 131 
 TYPE_2__* ALaw_Formats ; 
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int G711_GetFormatIndex (TYPE_4__*) ; 
 int /*<<< orphan*/  MMSYSERR_INVALPARAM ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 TYPE_2__* PCM_Formats ; 
 TYPE_2__* ULaw_Formats ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
#define  WAVE_FORMAT_ALAW 130 
#define  WAVE_FORMAT_MULAW 129 
#define  WAVE_FORMAT_PCM 128 

__attribute__((used)) static	LRESULT	G711_FormatDetails(PACMFORMATDETAILSW afd, DWORD dwQuery)
{
    switch (dwQuery)
    {
    case ACM_FORMATDETAILSF_FORMAT:
	if (G711_GetFormatIndex(afd->pwfx) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;
	break;
    case ACM_FORMATDETAILSF_INDEX:
	afd->pwfx->wFormatTag = afd->dwFormatTag;
	switch (afd->dwFormatTag)
        {
	case WAVE_FORMAT_PCM:
	    if (afd->dwFormatIndex >= ARRAY_SIZE(PCM_Formats)) return ACMERR_NOTPOSSIBLE;
	    afd->pwfx->nChannels = PCM_Formats[afd->dwFormatIndex].nChannels;
	    afd->pwfx->nSamplesPerSec = PCM_Formats[afd->dwFormatIndex].rate;
	    afd->pwfx->wBitsPerSample = PCM_Formats[afd->dwFormatIndex].nBits;
	    afd->pwfx->nBlockAlign = afd->pwfx->nChannels * 2;
	    afd->pwfx->nAvgBytesPerSec = afd->pwfx->nSamplesPerSec * afd->pwfx->nBlockAlign;
	    break;
	case WAVE_FORMAT_ALAW:
	    if (afd->dwFormatIndex >= ARRAY_SIZE(ALaw_Formats)) return ACMERR_NOTPOSSIBLE;
	    afd->pwfx->nChannels = ALaw_Formats[afd->dwFormatIndex].nChannels;
	    afd->pwfx->nSamplesPerSec = ALaw_Formats[afd->dwFormatIndex].rate;
	    afd->pwfx->wBitsPerSample = ALaw_Formats[afd->dwFormatIndex].nBits;
	    afd->pwfx->nBlockAlign = ALaw_Formats[afd->dwFormatIndex].nChannels;
	    afd->pwfx->nAvgBytesPerSec = afd->pwfx->nSamplesPerSec * afd->pwfx->nChannels;
            afd->pwfx->cbSize = 0;
	    break;
	case WAVE_FORMAT_MULAW:
	    if (afd->dwFormatIndex >= ARRAY_SIZE(ULaw_Formats)) return ACMERR_NOTPOSSIBLE;
	    afd->pwfx->nChannels = ULaw_Formats[afd->dwFormatIndex].nChannels;
	    afd->pwfx->nSamplesPerSec = ULaw_Formats[afd->dwFormatIndex].rate;
	    afd->pwfx->wBitsPerSample = ULaw_Formats[afd->dwFormatIndex].nBits;
	    afd->pwfx->nBlockAlign = ULaw_Formats[afd->dwFormatIndex].nChannels;
	    afd->pwfx->nAvgBytesPerSec = afd->pwfx->nSamplesPerSec * afd->pwfx->nChannels;
            afd->pwfx->cbSize = 0;
	    break;
	default:
            WARN("Unsupported tag %08x\n", afd->dwFormatTag);
	    return MMSYSERR_INVALPARAM;
	}
	break;
    default:
	WARN("Unsupported query %08x\n", dwQuery);
	return MMSYSERR_NOTSUPPORTED;
    }
    afd->fdwSupport = ACMDRIVERDETAILS_SUPPORTF_CODEC;
    afd->szFormat[0] = 0; /* let MSACM format this for us... */

    return MMSYSERR_NOERROR;
}