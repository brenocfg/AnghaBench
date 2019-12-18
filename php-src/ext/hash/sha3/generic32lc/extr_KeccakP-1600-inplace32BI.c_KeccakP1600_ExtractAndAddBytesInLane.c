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
typedef  unsigned char const UINT8 ;
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  fromBitInterleaving (int,int,int,int,int,int,int) ; 

void KeccakP1600_ExtractAndAddBytesInLane(const void *state, unsigned int lanePosition, const unsigned char *input, unsigned char *output, unsigned int offset, unsigned int length)
{
    UINT32 *stateAsHalfLanes = (UINT32*)state;
    UINT32 low, high, temp, temp0, temp1;
    UINT8 laneAsBytes[8];
    unsigned int i;

    fromBitInterleaving(stateAsHalfLanes[lanePosition*2], stateAsHalfLanes[lanePosition*2+1], low, high, temp, temp0, temp1);
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    *((UINT32*)(laneAsBytes+0)) = low;
    *((UINT32*)(laneAsBytes+4)) = high;
#else
    laneAsBytes[0] = low & 0xFF;
    laneAsBytes[1] = (low >> 8) & 0xFF;
    laneAsBytes[2] = (low >> 16) & 0xFF;
    laneAsBytes[3] = (low >> 24) & 0xFF;
    laneAsBytes[4] = high & 0xFF;
    laneAsBytes[5] = (high >> 8) & 0xFF;
    laneAsBytes[6] = (high >> 16) & 0xFF;
    laneAsBytes[7] = (high >> 24) & 0xFF;
#endif
    for(i=0; i<length; i++)
        output[i] = input[i] ^ laneAsBytes[offset+i];
}