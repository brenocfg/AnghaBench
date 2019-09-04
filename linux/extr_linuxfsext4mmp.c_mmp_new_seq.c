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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ EXT4_MMP_SEQ_MAX ; 
 scalar_t__ prandom_u32 () ; 

__attribute__((used)) static unsigned int mmp_new_seq(void)
{
	u32 new_seq;

	do {
		new_seq = prandom_u32();
	} while (new_seq > EXT4_MMP_SEQ_MAX);

	return new_seq;
}