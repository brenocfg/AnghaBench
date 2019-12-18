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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BATADV_TQ_LOCAL_WINDOW_SIZE ; 
 scalar_t__ test_bit (scalar_t__,unsigned long const*) ; 

__attribute__((used)) static inline bool batadv_test_bit(const unsigned long *seq_bits,
				   u32 last_seqno, u32 curr_seqno)
{
	s32 diff;

	diff = last_seqno - curr_seqno;
	if (diff < 0 || diff >= BATADV_TQ_LOCAL_WINDOW_SIZE)
		return false;
	return test_bit(diff, seq_bits) != 0;
}