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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ BATADV_TQ_LOCAL_WINDOW_SIZE ; 
 int /*<<< orphan*/  bitmap_shift_left (unsigned long*,unsigned long*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void batadv_bitmap_shift_left(unsigned long *seq_bits, s32 n)
{
	if (n <= 0 || n >= BATADV_TQ_LOCAL_WINDOW_SIZE)
		return;

	bitmap_shift_left(seq_bits, seq_bits, n, BATADV_TQ_LOCAL_WINDOW_SIZE);
}