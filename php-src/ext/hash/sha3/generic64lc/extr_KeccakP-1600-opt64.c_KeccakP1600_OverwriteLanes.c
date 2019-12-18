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
 int /*<<< orphan*/  memcpy (void*,unsigned char const*,unsigned int) ; 

void KeccakP1600_OverwriteLanes(void *state, const unsigned char *data, unsigned int laneCount)
{
#if (PLATFORM_BYTE_ORDER == IS_LITTLE_ENDIAN)
#ifdef KeccakP1600_useLaneComplementing
    unsigned int lanePosition;

    for(lanePosition=0; lanePosition<laneCount; lanePosition++)
        if ((lanePosition == 1) || (lanePosition == 2) || (lanePosition == 8) || (lanePosition == 12) || (lanePosition == 17) || (lanePosition == 20))
            ((UINT64*)state)[lanePosition] = ~((const UINT64*)data)[lanePosition];
        else
            ((UINT64*)state)[lanePosition] = ((const UINT64*)data)[lanePosition];
#else
    memcpy(state, data, laneCount*8);
#endif
#else
#error "Not yet implemented"
#endif
}