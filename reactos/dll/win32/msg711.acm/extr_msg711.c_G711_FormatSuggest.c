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
struct TYPE_5__ {int nChannels; int nSamplesPerSec; int wFormatTag; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; } ;
struct TYPE_4__ {int cbwfxSrc; int cbwfxDst; int fdwSuggest; TYPE_2__* pwfxSrc; TYPE_2__* pwfxDst; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMDRVFORMATSUGGEST ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
 int ACM_FORMATSUGGESTF_NCHANNELS ; 
 int ACM_FORMATSUGGESTF_NSAMPLESPERSEC ; 
 int ACM_FORMATSUGGESTF_WBITSPERSAMPLE ; 
 int ACM_FORMATSUGGESTF_WFORMATTAG ; 
 int G711_GetFormatIndex (TYPE_2__*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
#define  WAVE_FORMAT_ALAW 130 
#define  WAVE_FORMAT_MULAW 129 
#define  WAVE_FORMAT_PCM 128 

__attribute__((used)) static	LRESULT	G711_FormatSuggest(PACMDRVFORMATSUGGEST adfs)
{
    /* some tests ... */
    if (adfs->cbwfxSrc < sizeof(PCMWAVEFORMAT) ||
	adfs->cbwfxDst < sizeof(PCMWAVEFORMAT) ||
	G711_GetFormatIndex(adfs->pwfxSrc) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;
    /* FIXME: should do those tests against the real size (according to format tag */

    /* If no suggestion for destination, then copy source value */
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_NCHANNELS))
	adfs->pwfxDst->nChannels = adfs->pwfxSrc->nChannels;
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_NSAMPLESPERSEC))
        adfs->pwfxDst->nSamplesPerSec = adfs->pwfxSrc->nSamplesPerSec;

    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_WBITSPERSAMPLE))
    {
	if (adfs->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM)
            adfs->pwfxDst->wBitsPerSample = 8;
        else
            adfs->pwfxDst->wBitsPerSample = 16;
    }
    if (!(adfs->fdwSuggest & ACM_FORMATSUGGESTF_WFORMATTAG))
    {
	switch (adfs->pwfxSrc->wFormatTag)
        {
        case WAVE_FORMAT_PCM:   adfs->pwfxDst->wFormatTag = WAVE_FORMAT_ALAW; break;
        case WAVE_FORMAT_ALAW:  adfs->pwfxDst->wFormatTag = WAVE_FORMAT_PCM; break;
        case WAVE_FORMAT_MULAW: adfs->pwfxDst->wFormatTag = WAVE_FORMAT_PCM; break;
        }
    }
    /* check if result is ok */
    if (G711_GetFormatIndex(adfs->pwfxDst) == 0xFFFFFFFF) return ACMERR_NOTPOSSIBLE;

    /* recompute other values */
    switch (adfs->pwfxDst->wFormatTag)
    {
    case WAVE_FORMAT_PCM:
        adfs->pwfxDst->nBlockAlign = adfs->pwfxDst->nChannels * 2;
        adfs->pwfxDst->nAvgBytesPerSec = adfs->pwfxDst->nSamplesPerSec * adfs->pwfxDst->nBlockAlign;
        break;
    case WAVE_FORMAT_ALAW:
        adfs->pwfxDst->nBlockAlign = adfs->pwfxDst->nChannels;
        adfs->pwfxDst->nAvgBytesPerSec = adfs->pwfxDst->nSamplesPerSec * adfs->pwfxSrc->nChannels;
        break;
    case WAVE_FORMAT_MULAW:
        adfs->pwfxDst->nBlockAlign = adfs->pwfxDst->nChannels;
        adfs->pwfxDst->nAvgBytesPerSec = adfs->pwfxDst->nSamplesPerSec * adfs->pwfxSrc->nChannels;
        break;
    }

    return MMSYSERR_NOERROR;
}