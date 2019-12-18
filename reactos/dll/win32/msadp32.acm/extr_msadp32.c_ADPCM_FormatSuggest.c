#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ wFormatTag; int nChannels; int nSamplesPerSec; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; } ;
struct TYPE_4__ {int cbwfxSrc; int cbwfxDst; int fdwSuggest; TYPE_2__* pwfxDst; TYPE_2__* pwfxSrc; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMDRVFORMATSUGGEST ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  ADPCMWAVEFORMAT ;
typedef  int /*<<< orphan*/  ADPCMCOEFSET ;

/* Variables and functions */
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
 int ACM_FORMATSUGGESTF_NCHANNELS ; 
 int ACM_FORMATSUGGESTF_NSAMPLESPERSEC ; 
 int ACM_FORMATSUGGESTF_WBITSPERSAMPLE ; 
 int ACM_FORMATSUGGESTF_WFORMATTAG ; 
 int ADPCM_GetFormatIndex (TYPE_2__*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
#define  WAVE_FORMAT_ADPCM 129 
#define  WAVE_FORMAT_PCM 128 
 int /*<<< orphan*/  init_wfx_adpcm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	LRESULT	ADPCM_FormatSuggest(PACMDRVFORMATSUGGEST adfs)
{
    /* some tests ... */
    if (adfs->cbwfxSrc < sizeof(PCMWAVEFORMAT) ||
	adfs->cbwfxDst < sizeof(PCMWAVEFORMAT) ||
	adfs->pwfxSrc->wFormatTag == adfs->pwfxDst->wFormatTag ||
	ADPCM_GetFormatIndex(adfs->pwfxSrc) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;
    /* FIXME: should do those tests against the real size (according to format tag */

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
            adfs->pwfxDst->wFormatTag = WAVE_FORMAT_ADPCM;
        else
            adfs->pwfxDst->wFormatTag = WAVE_FORMAT_PCM;
    }

    /* recompute other values */
    switch (adfs->pwfxDst->wFormatTag)
    {
    case WAVE_FORMAT_PCM:
        adfs->pwfxDst->nBlockAlign = (adfs->pwfxDst->nChannels * adfs->pwfxDst->wBitsPerSample) / 8;
        adfs->pwfxDst->nAvgBytesPerSec = adfs->pwfxDst->nSamplesPerSec * adfs->pwfxDst->nBlockAlign;
        /* check if result is ok */
        if (ADPCM_GetFormatIndex(adfs->pwfxDst) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;
        break;
    case WAVE_FORMAT_ADPCM:
        if (adfs->cbwfxDst < sizeof(ADPCMWAVEFORMAT) + (7 - 1) * sizeof(ADPCMCOEFSET))
            return ACMERR_NOTPOSSIBLE;
        init_wfx_adpcm((ADPCMWAVEFORMAT*)adfs->pwfxDst);
        /* check if result is ok */
        if (ADPCM_GetFormatIndex(adfs->pwfxDst) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;
        break;
    default:
        return ACMERR_NOTPOSSIBLE;
    }

    return MMSYSERR_NOERROR;
}