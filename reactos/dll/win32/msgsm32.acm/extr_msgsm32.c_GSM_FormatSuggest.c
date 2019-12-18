#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_7__ {int nSamplesPerSec; int wFormatTag; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; int cbSize; int /*<<< orphan*/  nChannels; } ;
struct TYPE_6__ {int wSamplesPerBlock; } ;
struct TYPE_5__ {int cbwfxSrc; int cbwfxDst; int fdwSuggest; TYPE_3__* pwfxDst; TYPE_3__* pwfxSrc; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMDRVFORMATSUGGEST ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ GSM610WAVEFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
 int ACM_FORMATSUGGESTF_NCHANNELS ; 
 int ACM_FORMATSUGGESTF_NSAMPLESPERSEC ; 
 int ACM_FORMATSUGGESTF_WBITSPERSAMPLE ; 
 int ACM_FORMATSUGGESTF_WFORMATTAG ; 
 int /*<<< orphan*/  GSM_FormatValidate (TYPE_3__*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
#define  WAVE_FORMAT_GSM610 129 
#define  WAVE_FORMAT_PCM 128 

__attribute__((used)) static	LRESULT	GSM_FormatSuggest(PACMDRVFORMATSUGGEST adfs)
{
    /* some tests ... */
    if (adfs->cbwfxSrc < sizeof(PCMWAVEFORMAT) ||
	adfs->cbwfxDst < sizeof(PCMWAVEFORMAT) ||
	!GSM_FormatValidate(adfs->pwfxSrc)) return ACMERR_NOTPOSSIBLE;
    /* FIXME: should do those tests against the real size (according to format tag */

    /* If no suggestion for destination, then copy source value */
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_NCHANNELS))
	adfs->pwfxDst->nChannels = adfs->pwfxSrc->nChannels;
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_NSAMPLESPERSEC))
        adfs->pwfxDst->nSamplesPerSec = adfs->pwfxSrc->nSamplesPerSec;

    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_WBITSPERSAMPLE))
    {
	if (adfs->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM)
            adfs->pwfxDst->wBitsPerSample = 0;
        else
            adfs->pwfxDst->wBitsPerSample = 16;
    }
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_WFORMATTAG))
    {
	switch (adfs->pwfxSrc->wFormatTag)
        {
        case WAVE_FORMAT_PCM: adfs->pwfxDst->wFormatTag = WAVE_FORMAT_GSM610; break;
        case WAVE_FORMAT_GSM610: adfs->pwfxDst->wFormatTag = WAVE_FORMAT_PCM; break;
        }
    }

    /* recompute other values */
    switch (adfs->pwfxDst->wFormatTag)
    {
    case WAVE_FORMAT_PCM:
        adfs->pwfxDst->nBlockAlign = 2;
        adfs->pwfxDst->nAvgBytesPerSec = adfs->pwfxDst->nSamplesPerSec * 2;
        break;
    case WAVE_FORMAT_GSM610:
        if (adfs->pwfxDst->cbSize < sizeof(WORD))
            return ACMERR_NOTPOSSIBLE;
        adfs->pwfxDst->nBlockAlign = 65;
        adfs->pwfxDst->nAvgBytesPerSec = adfs->pwfxDst->nSamplesPerSec * 65 / 320;
        ((GSM610WAVEFORMAT*)adfs->pwfxDst)->wSamplesPerBlock = 320;
        break;
    default:
        return ACMERR_NOTPOSSIBLE;
    }

    /* check if result is ok */
    if (!GSM_FormatValidate(adfs->pwfxDst)) return ACMERR_NOTPOSSIBLE;
    return MMSYSERR_NOERROR;
}