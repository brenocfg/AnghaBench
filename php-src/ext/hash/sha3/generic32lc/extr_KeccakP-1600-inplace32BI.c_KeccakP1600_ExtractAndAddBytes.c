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
 int /*<<< orphan*/  KeccakP1600_ExtractAndAddBytesInLane ; 
 int /*<<< orphan*/  KeccakP1600_ExtractAndAddLanes ; 
 int /*<<< orphan*/  SnP_ExtractAndAddBytes (void const*,unsigned char const*,unsigned char*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void KeccakP1600_ExtractAndAddBytes(const void *state, const unsigned char *input, unsigned char *output, unsigned int offset, unsigned int length)
{
    SnP_ExtractAndAddBytes(state, input, output, offset, length, KeccakP1600_ExtractAndAddLanes, KeccakP1600_ExtractAndAddBytesInLane, 8);
}