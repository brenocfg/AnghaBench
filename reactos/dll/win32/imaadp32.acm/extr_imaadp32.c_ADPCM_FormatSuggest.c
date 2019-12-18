#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ wFormatTag; int nChannels; int nSamplesPerSec; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; } ;
struct TYPE_7__ {int /*<<< orphan*/  wSamplesPerBlock; } ;
struct TYPE_6__ {int cbwfxSrc; int cbwfxDst; int fdwSuggest; TYPE_4__* pwfxDst; TYPE_4__* pwfxSrc; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMDRVFORMATSUGGEST ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ IMAADPCMWAVEFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
 int ACM_FORMATSUGGESTF_NCHANNELS ; 
 int ACM_FORMATSUGGESTF_NSAMPLESPERSEC ; 
 int ACM_FORMATSUGGESTF_WBITSPERSAMPLE ; 
 int ACM_FORMATSUGGESTF_WFORMATTAG ; 
 int ADPCM_GetFormatIndex (TYPE_4__*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
#define  WAVE_FORMAT_IMA_ADPCM 129 
#define  WAVE_FORMAT_PCM 128 
 int /*<<< orphan*/  init_wfx_ima_adpcm (TYPE_2__*) ; 

__attribute__((used)) static	LRESULT	ADPCM_FormatSuggest(PACMDRVFORMATSUGGEST adfs)
{
    /* some tests ... */
    if (adfs->cbwfxSrc < sizeof(PCMWAVEFORMAT) ||
	adfs->cbwfxDst < sizeof(PCMWAVEFORMAT) ||
	adfs->pwfxSrc->wFormatTag == adfs->pwfxDst->wFormatTag ||
	ADPCM_GetFormatIndex(adfs->pwfxSrc) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;

    /* If no suggestion for destination, then copy source value */
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_NCHANNELS))
	adfs->pwfxDst->nChannels = adfs->pwfxSrc->nChannels;
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_NSAMPLESPERSEC))
        adfs->pwfxDst->nSamplesPerSec = adfs->pwfxSrc->nSamplesPerSec;

    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_WBITSPERSAMPLE))
    {
	if (adfs->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM)
            adfs->pwfxDst->wBitsPerSample = 4;
        else
            adfs->pwfxDst->wBitsPerSample = 16;
    }
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_WFORMATTAG))
    {
	if (adfs->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM)
            adfs->pwfxDst->wFormatTag = WAVE_FORMAT_IMA_ADPCM;
        else
            adfs->pwfxDst->wFormatTag = WAVE_FORMAT_PCM;
    }

    /* recompute other values */
    switch (adfs->pwfxDst->wFormatTag)
    {
    case WAVE_FORMAT_PCM:
        if (adfs->cbwfxSrc < sizeof(IMAADPCMWAVEFORMAT)) return ACMERR_NOTPOSSIBLE;
        adfs->pwfxDst->nBlockAlign = (adfs->pwfxDst->nChannels * adfs->pwfxDst->wBitsPerSample) / 8;
        adfs->pwfxDst->nAvgBytesPerSec = adfs->pwfxDst->nSamplesPerSec * adfs->pwfxDst->nBlockAlign;
        /* check if result is ok */
        if (ADPCM_GetFormatIndex(adfs->pwfxDst) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;
        break;
    case WAVE_FORMAT_IMA_ADPCM:
        if (adfs->cbwfxDst < sizeof(IMAADPCMWAVEFORMAT)) return ACMERR_NOTPOSSIBLE;
        init_wfx_ima_adpcm((IMAADPCMWAVEFORMAT*)adfs->pwfxDst);
        /* FIXME: not handling header overhead */
        TRACE("setting spb=%u\n", ((IMAADPCMWAVEFORMAT*)adfs->pwfxDst)->wSamplesPerBlock);
        /* check if result is ok */
        if (ADPCM_GetFormatIndex(adfs->pwfxDst) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;
        break;
    default:
        return ACMERR_NOTPOSSIBLE;
    }

    return MMSYSERR_NOERROR;
}