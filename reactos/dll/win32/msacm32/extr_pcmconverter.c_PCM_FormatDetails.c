#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nChannels; int rate; int nBits; } ;
struct TYPE_8__ {int nChannels; int nSamplesPerSec; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; void* wFormatTag; } ;
struct TYPE_7__ {size_t dwFormatIndex; int cbwfx; scalar_t__* szFormat; int /*<<< orphan*/  fdwSupport; void* dwFormatTag; TYPE_3__* pwfx; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_1__* PACMFORMATDETAILSW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACMDRIVERDETAILS_SUPPORTF_CONVERTER ; 
 int /*<<< orphan*/  ACMERR_NOTPOSSIBLE ; 
#define  ACM_FORMATDETAILSF_FORMAT 129 
#define  ACM_FORMATDETAILSF_INDEX 128 
 size_t ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
 TYPE_4__* PCM_Formats ; 
 int PCM_GetFormatIndex (TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 void* WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static	LRESULT	PCM_FormatDetails(PACMFORMATDETAILSW afd, DWORD dwQuery)
{
    TRACE("(%p, %08x)\n", afd, dwQuery);

    switch (dwQuery) {
    case ACM_FORMATDETAILSF_FORMAT:
	if (PCM_GetFormatIndex(afd->pwfx) == 0xFFFFFFFF) {
            WARN("not possible\n");
            return ACMERR_NOTPOSSIBLE;
        }
	break;
    case ACM_FORMATDETAILSF_INDEX:
	assert(afd->dwFormatIndex < ARRAY_SIZE(PCM_Formats));
	afd->pwfx->wFormatTag = WAVE_FORMAT_PCM;
	afd->pwfx->nChannels = PCM_Formats[afd->dwFormatIndex].nChannels;
	afd->pwfx->nSamplesPerSec = PCM_Formats[afd->dwFormatIndex].rate;
	afd->pwfx->wBitsPerSample = PCM_Formats[afd->dwFormatIndex].nBits;
	/* native MSACM uses a PCMWAVEFORMAT structure, so cbSize is not
	 * accessible afd->pwfx->cbSize = 0;
	 */
	afd->pwfx->nBlockAlign =
	    (afd->pwfx->nChannels * afd->pwfx->wBitsPerSample) / 8;
	afd->pwfx->nAvgBytesPerSec =
	    afd->pwfx->nSamplesPerSec * afd->pwfx->nBlockAlign;
	break;
    default:
	WARN("Unsupported query %08x\n", dwQuery);
	return MMSYSERR_NOTSUPPORTED;
    }

    afd->dwFormatTag = WAVE_FORMAT_PCM;
    afd->fdwSupport = ACMDRIVERDETAILS_SUPPORTF_CONVERTER;
    afd->szFormat[0] = 0; /* let MSACM format this for us... */
    afd->cbwfx = sizeof(PCMWAVEFORMAT);

    return MMSYSERR_NOERROR;
}