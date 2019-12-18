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
struct TYPE_9__ {int fdwSize; int cbSrcLength; int cbDstLength; } ;
struct TYPE_8__ {int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_7__ {int /*<<< orphan*/  wFormatTag; } ;
typedef  TYPE_3__* PACMDRVSTREAMSIZE ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_4__ ACMDRVSTREAMINSTANCE ;

/* Variables and functions */
#define  ACM_STREAMSIZEF_DESTINATION 129 
#define  ACM_STREAMSIZEF_SOURCE 128 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int /*<<< orphan*/  WAVE_FORMAT_ALAW ; 
 int /*<<< orphan*/  WAVE_FORMAT_MULAW ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 

__attribute__((used)) static	LRESULT G711_StreamSize(const ACMDRVSTREAMINSTANCE *adsi, PACMDRVSTREAMSIZE adss)
{
    switch (adss->fdwSize)
    {
    case ACM_STREAMSIZEF_DESTINATION:
	/* cbDstLength => cbSrcLength */
	if (adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM &&
	    (adsi->pwfxDst->wFormatTag == WAVE_FORMAT_ALAW ||
             adsi->pwfxDst->wFormatTag == WAVE_FORMAT_MULAW))
        {
	    adss->cbSrcLength = adss->cbDstLength * 2;
	}
        else if ((adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_ALAW ||
                  adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_MULAW) &&
                 adsi->pwfxDst->wFormatTag == WAVE_FORMAT_PCM)
        {
	    adss->cbSrcLength = adss->cbDstLength / 2;
	}
        else if ((adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_ALAW ||
                  adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_MULAW) &&
                 (adsi->pwfxDst->wFormatTag == WAVE_FORMAT_ALAW ||
                  adsi->pwfxDst->wFormatTag == WAVE_FORMAT_MULAW))
        {
	    adss->cbSrcLength = adss->cbDstLength;
        }
        else
        {
	    return MMSYSERR_NOTSUPPORTED;
	}
	break;
    case ACM_STREAMSIZEF_SOURCE:
	/* cbSrcLength => cbDstLength */
	if (adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_PCM &&
	    (adsi->pwfxDst->wFormatTag == WAVE_FORMAT_ALAW ||
             adsi->pwfxDst->wFormatTag == WAVE_FORMAT_MULAW))
        {
	    adss->cbDstLength = adss->cbSrcLength / 2;
	}
        else if ((adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_ALAW ||
                  adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_MULAW) &&
                 adsi->pwfxDst->wFormatTag == WAVE_FORMAT_PCM)
        {
	    adss->cbDstLength = adss->cbSrcLength * 2;
	}
        else if ((adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_ALAW ||
                  adsi->pwfxSrc->wFormatTag == WAVE_FORMAT_MULAW) &&
                 (adsi->pwfxDst->wFormatTag == WAVE_FORMAT_ALAW ||
                  adsi->pwfxDst->wFormatTag == WAVE_FORMAT_MULAW))
        {
	    adss->cbDstLength = adss->cbSrcLength;
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