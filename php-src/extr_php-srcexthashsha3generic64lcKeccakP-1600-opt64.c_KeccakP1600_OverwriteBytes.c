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
 int /*<<< orphan*/  KeccakP1600_OverwriteBytesInLane ; 
 int /*<<< orphan*/  KeccakP1600_OverwriteLanes ; 
 int /*<<< orphan*/  SnP_OverwriteBytes (void*,unsigned char const*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void KeccakP1600_OverwriteBytes(void *state, const unsigned char *data, unsigned int offset, unsigned int length)
{
    SnP_OverwriteBytes(state, data, offset, length, KeccakP1600_OverwriteLanes, KeccakP1600_OverwriteBytesInLane, 8);
}