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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* pwfxDst; TYPE_1__* pwfxSrc; } ;
struct TYPE_9__ {int fdwSize; int cbDstLength; int cbSrcLength; } ;
struct TYPE_8__ {int nAvgBytesPerSec; int nSamplesPerSec; int nBlockAlign; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_7__ {int nBlockAlign; int nAvgBytesPerSec; int nSamplesPerSec; int /*<<< orphan*/  wFormatTag; } ;
typedef  TYPE_3__* PACMDRVSTREAMSIZE ;
typedef  TYPE_4__* PACMDRVSTREAMINSTANCE ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_STREAMSIZEF_DESTINATION 129 
#define  ACM_STREAMSIZEF_SOURCE 128 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  WAVE_FORMAT_MPEG ; 
 int /*<<< orphan*/  WAVE_FORMAT_MPEGLAYER3 ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 

__attribute__((used)) static	LRESULT MPEG3_StreamSize(PACMDRVSTREAMINSTANCE adsi, PACMDRVSTREAMSIZE adss)
{
    DWORD nblocks;

    switch (adss->fdwSize)
    {
    case ACM_STREAMSIZEF_DESTINATION:
	/* cbDstLength => cbSrcLength */
	if (adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM &&
            (adsi->pwfxDst->wFormatTag == WAVE_FORMAT_MPEGLAYER3 ||
             adsi->pwfxDst->wFormatTag == WAVE_FORMAT_MPEG))
        {
            nblocks = (adss->cbDstLength - 3000) / (DWORD)(adsi->pwfxDst->nAvgBytesPerSec * 1152 / adsi->pwfxDst->nSamplesPerSec + 0.5);
            if (nblocks == 0)
                return ACMERR_NOTPOSSIBLE;
            adss->cbSrcLength = nblocks * 1152 * adsi->pwfxSrc->nBlockAlign;
	}
        else if ((adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_MPEGLAYER3 ||
                 adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_MPEG) &&
                 adsi->pwfxDst->wFormatTag == WAVE_FORMAT_PCM)
        {
            nblocks = adss->cbDstLength / (adsi->pwfxDst->nBlockAlign * 1152);
            if (nblocks == 0)
                return ACMERR_NOTPOSSIBLE;
            adss->cbSrcLength = nblocks * (DWORD)(adsi->pwfxSrc->nAvgBytesPerSec * 1152 / adsi->pwfxSrc->nSamplesPerSec);
	}
        else
        {
	    return MMSYSERR_NOTSUPPORTED;
	}
	break;
    case ACM_STREAMSIZEF_SOURCE:
	/* cbSrcLength => cbDstLength */
	if (adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM &&
            (adsi->pwfxDst->wFormatTag == WAVE_FORMAT_MPEGLAYER3 ||
             adsi->pwfxDst->wFormatTag == WAVE_FORMAT_MPEG))
        {
            nblocks = adss->cbSrcLength / (adsi->pwfxSrc->nBlockAlign * 1152);
            if (adss->cbSrcLength % (DWORD)(adsi->pwfxSrc->nBlockAlign * 1152))
                /* Round block count up. */
                nblocks++;
            if (nblocks == 0)
                return ACMERR_NOTPOSSIBLE;
            adss->cbDstLength = 3000 + nblocks * (DWORD)(adsi->pwfxDst->nAvgBytesPerSec * 1152 / adsi->pwfxDst->nSamplesPerSec + 0.5);
	}
        else if ((adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_MPEGLAYER3 ||
                 adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_MPEG) &&
                 adsi->pwfxDst->wFormatTag == WAVE_FORMAT_PCM)
        {
            nblocks = adss->cbSrcLength / (DWORD)(adsi->pwfxSrc->nAvgBytesPerSec * 1152 / adsi->pwfxSrc->nSamplesPerSec);
            if (adss->cbSrcLength % (DWORD)(adsi->pwfxSrc->nAvgBytesPerSec * 1152 / adsi->pwfxSrc->nSamplesPerSec))
                /* Round block count up. */
                nblocks++;
            if (nblocks == 0)
                return ACMERR_NOTPOSSIBLE;
            adss->cbDstLength = nblocks * 1152 * adsi->pwfxDst->nBlockAlign;
	}
        else
        {
	    return MMSYSERR_NOTSUPPORTED;
	}
	break;
    default:
	WARN("Unsupported query %08x\n", adss->fdwSize);
	return MMSYSERR_NOTSUPPORTED;
    }
    return MMSYSERR_NOERROR;
}