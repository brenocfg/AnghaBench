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

/* Variables and functions */
 int /*<<< orphan*/  KeccakP1600_AddBytesInLane (void*,unsigned int,unsigned char const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  KeccakP1600_SetBytesInLaneToZero (void*,unsigned int,unsigned int,unsigned int) ; 

void KeccakP1600_OverwriteBytesInLane(void *state, unsigned int lanePosition, const unsigned char *data, unsigned int offset, unsigned int length)
{
    KeccakP1600_SetBytesInLaneToZero(state, lanePosition, offset, length);
    KeccakP1600_AddBytesInLane(state, lanePosition, data, offset, length);
}