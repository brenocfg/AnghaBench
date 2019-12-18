#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_uint32 ;
typedef  int npy_int32 ;
struct TYPE_3__ {int* blocks; int length; } ;
typedef  TYPE_1__ BigInt ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ASSERT (int) ; 
 int c_BigInt_MaxBlocks ; 

__attribute__((used)) static void
BigInt_ShiftLeft(BigInt *result, npy_uint32 shift)
{
    npy_uint32 shiftBlocks = shift / 32;
    npy_uint32 shiftBits = shift % 32;

    /* process blocks high to low so that we can safely process in place */
    const npy_uint32 *pInBlocks = result->blocks;
    npy_int32 inLength = result->length;
    npy_uint32 *pInCur, *pOutCur;

    DEBUG_ASSERT(inLength + shiftBlocks < c_BigInt_MaxBlocks);
    DEBUG_ASSERT(shift != 0);

    /* check if the shift is block aligned */
    if (shiftBits == 0) {
        npy_uint32 i;

        /* copy blocks from high to low */
        for (pInCur = result->blocks + result->length,
                 pOutCur = pInCur + shiftBlocks;
                 pInCur >= pInBlocks;
                 --pInCur, --pOutCur) {
            *pOutCur = *pInCur;
        }

        /* zero the remaining low blocks */
        for (i  = 0; i < shiftBlocks; ++i) {
            result->blocks[i] = 0;
        }

        result->length += shiftBlocks;
    }
    /* else we need to shift partial blocks */
    else {
        npy_uint32 i;
        npy_int32 inBlockIdx = inLength - 1;
        npy_uint32 outBlockIdx = inLength + shiftBlocks;

        /* output the initial blocks */
        const npy_uint32 lowBitsShift = (32 - shiftBits);
        npy_uint32 highBits = 0;
        npy_uint32 block = result->blocks[inBlockIdx];
        npy_uint32 lowBits = block >> lowBitsShift;

        /* set the length to hold the shifted blocks */
        DEBUG_ASSERT(outBlockIdx < c_BigInt_MaxBlocks);
        result->length = outBlockIdx + 1;

        while (inBlockIdx > 0) {
            result->blocks[outBlockIdx] = highBits | lowBits;
            highBits = block << shiftBits;

            --inBlockIdx;
            --outBlockIdx;

            block = result->blocks[inBlockIdx];
            lowBits = block >> lowBitsShift;
        }

        /* output the final blocks */
        DEBUG_ASSERT(outBlockIdx == shiftBlocks + 1);
        result->blocks[outBlockIdx] = highBits | lowBits;
        result->blocks[outBlockIdx-1] = block << shiftBits;

        /* zero the remaining low blocks */
        for (i = 0; i < shiftBlocks; ++i) {
            result->blocks[i] = 0;
        }

        /* check if the terminating block has no set bits */
        if (result->blocks[result->length - 1] == 0) {
            --result->length;
        }
    }
}