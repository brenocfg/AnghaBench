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
struct rsc {int msr; unsigned int conj; } ;

/* Variables and functions */
 unsigned int AUDIO_SLOT_BLOCK_NUM ; 

__attribute__((used)) static int rsc_next_conj(struct rsc *rsc)
{
	unsigned int i;
	for (i = 0; (i < 8) && (!(rsc->msr & (0x1 << i))); )
		i++;
	rsc->conj += (AUDIO_SLOT_BLOCK_NUM >> i);
	return rsc->conj;
}