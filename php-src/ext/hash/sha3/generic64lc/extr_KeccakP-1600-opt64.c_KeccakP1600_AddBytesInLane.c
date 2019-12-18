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
typedef  unsigned int UINT64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned char const*,unsigned int) ; 

void KeccakP1600_AddBytesInLane(void *state, unsigned int lanePosition, const unsigned char *data, unsigned int offset, unsigned int length)
{
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
    UINT64 lane;
    if (length == 0)
        return;
    if (length == 1)
        lane = data[0];
    else {
        lane = 0;
        memcpy(&lane, data, length);
    }
    lane <<= offset*8;
#else
    UINT64 lane = 0;
    unsigned int i;
    for(i=0; i<length; i++)
        lane |= ((UINT64)data[i]) << ((i+offset)*8);
#endif
    ((UINT64*)state)[lanePosition] ^= lane;
}