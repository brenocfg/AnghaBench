#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int,unsigned int) ; 

void KeccakP1600_OverwriteWithZeroes(void *state, unsigned int byteCount)
{
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
#ifdef KeccakP1600_useLaneComplementing
    unsigned int lanePosition;

    for(lanePosition=0; lanePosition<byteCount/8; lanePosition++)
        if ((lanePosition == 1) || (lanePosition == 2) || (lanePosition == 8) || (lanePosition == 12) || (lanePosition == 17) || (lanePosition == 20))
            ((UINT64*)state)[lanePosition] = ~0;
        else
            ((UINT64*)state)[lanePosition] = 0;
    if (byteCount%8 != 0) {
        lanePosition = byteCount/8;
        if ((lanePosition == 1) || (lanePosition == 2) || (lanePosition == 8) || (lanePosition == 12) || (lanePosition == 17) || (lanePosition == 20))
            memset((unsigned char*)state+lanePosition*8, 0xFF, byteCount%8);
        else
            memset((unsigned char*)state+lanePosition*8, 0, byteCount%8);
    }
#else
    memset(state, 0, byteCount);
#endif
#else
#error "Not yet implemented"
#endif
}