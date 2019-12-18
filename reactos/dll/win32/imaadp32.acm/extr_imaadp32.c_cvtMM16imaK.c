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
struct TYPE_9__ {int stepIndexL; } ;
struct TYPE_8__ {int wSamplesPerBlock; } ;
struct TYPE_7__ {scalar_t__ dwDriver; TYPE_1__* pwfxDst; } ;
struct TYPE_6__ {int nBlockAlign; } ;
typedef  TYPE_2__* PACMDRVSTREAMINSTANCE ;
typedef  TYPE_3__* LPIMAADPCMWAVEFORMAT ;
typedef  int* LPDWORD ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  TYPE_4__ AcmAdpcmData ;

/* Variables and functions */
 int R16 (unsigned char const*) ; 
 int /*<<< orphan*/  W16 (unsigned char*,int) ; 
 int generate_nibble (int,int*,int*) ; 
 int min (int,int) ; 

__attribute__((used)) static	void cvtMM16imaK(PACMDRVSTREAMINSTANCE adsi,
                         const unsigned char* src, LPDWORD nsrc,
                         unsigned char* dst, LPDWORD ndst)
{
    int		stepIndex;
    int		sample;
    BYTE 	code1, code2;
    int		nsamp_blk = ((LPIMAADPCMWAVEFORMAT)adsi->pwfxDst)->wSamplesPerBlock;
    int		nsamp;
    /* compute the number of entire blocks we can decode...
     * it's the min of the number of entire blocks in source buffer and the number
     * of entire blocks in destination buffer
     */
    DWORD	nblock = min(*nsrc / (nsamp_blk * 2),
                             *ndst / adsi->pwfxDst->nBlockAlign);

    *nsrc = nblock * (nsamp_blk * 2);
    *ndst = nblock * adsi->pwfxDst->nBlockAlign;

    stepIndex = ((AcmAdpcmData*)adsi->dwDriver)->stepIndexL;
    nsamp_blk--; /* so that we won't count the sample in header while filling the block */

    for (; nblock > 0; nblock--)
    {
        unsigned char*   in_dst = dst;

        /* generate header */
        /* FIXME: what about the last effective sample from previous block ??? */
        /* perhaps something like:
         *      sample += R16(src);
         *      clamp_sample(sample);
         * and with :
         *      + saving the sample in adsi->dwDriver when all blocks are done
         +      + reset should set the field in adsi->dwDriver to 0 too
         */
    	sample = R16(src); src += 2;
	W16(dst, sample); dst += 2;
	*dst = (unsigned char)(unsigned)stepIndex;
	dst += 2;

	for (nsamp = nsamp_blk; nsamp > 0; nsamp -= 2)
        {
            code1 = generate_nibble(R16(src), &stepIndex, &sample);
            src += 2;
            code2 = generate_nibble(R16(src), &stepIndex, &sample);
            src += 2;
            *dst++ = (code2 << 4) | code1;
	}
	dst = in_dst + adsi->pwfxDst->nBlockAlign;
    }
    ((AcmAdpcmData*)adsi->dwDriver)->stepIndexL = stepIndex;
}