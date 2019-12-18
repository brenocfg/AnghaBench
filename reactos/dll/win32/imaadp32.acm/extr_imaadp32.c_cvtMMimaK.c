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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int wSamplesPerBlock; } ;
struct TYPE_8__ {TYPE_2__* pwfxSrc; TYPE_1__* pwfxDst; } ;
struct TYPE_7__ {int nBlockAlign; } ;
struct TYPE_6__ {int wBitsPerSample; } ;
typedef  TYPE_3__* PACMDRVSTREAMINSTANCE ;
typedef  TYPE_4__* LPIMAADPCMWAVEFORMAT ;
typedef  int* LPDWORD ;
typedef  int DWORD ;

/* Variables and functions */
 int R16 (unsigned char const*) ; 
 int /*<<< orphan*/  W8_16 (unsigned char*,int,int) ; 
 int /*<<< orphan*/  clamp_step_index (int*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  process_nibble (unsigned char const,int*,int*) ; 

__attribute__((used)) static void cvtMMimaK(PACMDRVSTREAMINSTANCE adsi,
                    const unsigned char* src, LPDWORD nsrc,
                    unsigned char* dst, LPDWORD ndst)
{
    int sample;
    int stepIndex;
    int nsamp_blk = ((LPIMAADPCMWAVEFORMAT)adsi->pwfxSrc)->wSamplesPerBlock;
    int nsamp;
    int bytesPerSample = adsi->pwfxDst->wBitsPerSample / 8;
    /* compute the number of entire blocks we can decode...
     * it's the min of the number of entire blocks in source buffer and the number
     * of entire blocks in destination buffer
     */
    DWORD nblock = min(*nsrc / adsi->pwfxSrc->nBlockAlign, *ndst / (nsamp_blk * bytesPerSample));

    *nsrc = nblock * adsi->pwfxSrc->nBlockAlign;
    *ndst = nblock * nsamp_blk * bytesPerSample;

    nsamp_blk--; /* remove the sample in block header */
    for (; nblock > 0; nblock--)
    {
        const unsigned char* in_src = src;

        /* handle header first */
        sample = R16(src);
        stepIndex = (unsigned)*(src + 2);
        clamp_step_index(&stepIndex);
        src += 4;
        W8_16(dst, sample, bytesPerSample); dst += bytesPerSample;

        for (nsamp = nsamp_blk; nsamp > 0; nsamp -= 2)
        {
            process_nibble(*src, &stepIndex, &sample);
            W8_16(dst, sample, bytesPerSample); dst += bytesPerSample;
            process_nibble(*src++ >> 4, &stepIndex, &sample);
            W8_16(dst, sample, bytesPerSample); dst += bytesPerSample;
        }
        /* we have now to realign the source pointer on block */
        src = in_src + adsi->pwfxSrc->nBlockAlign;
    }
}