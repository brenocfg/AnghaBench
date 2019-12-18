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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {scalar_t__ wFormatTag; int nSamplesPerSec; int nBlockAlign; int nChannels; int cbSize; int nAvgBytesPerSec; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
struct TYPE_6__ {int wSamplesPerBlock; TYPE_1__ wfx; } ;
typedef  TYPE_2__ IMAADPCMWAVEFORMAT ;

/* Variables and functions */
 int ADPCM_GetFormatIndex (TYPE_1__*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ WAVE_FORMAT_IMA_ADPCM ; 

__attribute__((used)) static void     init_wfx_ima_adpcm(IMAADPCMWAVEFORMAT* awfx/*, DWORD nba*/)
{
    WAVEFORMATEX* pwfx = &awfx->wfx;

    /* we assume wFormatTag, nChannels, nSamplesPerSec and wBitsPerSample
     * have been initialized... */

    if (pwfx->wFormatTag != WAVE_FORMAT_IMA_ADPCM) {FIXME("wrong FT\n"); return;}
    if (ADPCM_GetFormatIndex(pwfx) == 0xFFFFFFFF) {FIXME("wrong fmt\n"); return;}

    switch (pwfx->nSamplesPerSec)
    {
    case  8000: pwfx->nBlockAlign = 256 * pwfx->nChannels;   break;
    case 11025: pwfx->nBlockAlign = 256 * pwfx->nChannels;   break;
    case 22050: pwfx->nBlockAlign = 512 * pwfx->nChannels;   break;
    case 44100: pwfx->nBlockAlign = 1024 * pwfx->nChannels;  break;
    default: /*pwfx->nBlockAlign = nba;*/  break;
    }
    pwfx->cbSize = sizeof(WORD);

    awfx->wSamplesPerBlock = (pwfx->nBlockAlign - (4 * pwfx->nChannels)) * (2 / pwfx->nChannels) + 1;
    pwfx->nAvgBytesPerSec = (pwfx->nSamplesPerSec * pwfx->nBlockAlign) / awfx->wSamplesPerBlock;
}