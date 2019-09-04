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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 siox_status_clean(u8 status_read, u8 status_written)
{
	/*
	 * bits 3:1 of status sample the respective bit in the status
	 * byte written in the previous cycle but inverted. So if you wrote the
	 * status word as 0xa before (counter = 0b101), it is expected to get
	 * back the counter bits as 0b010.
	 *
	 * So given the last status written this function toggles the there
	 * unset counter bits in the read value such that the counter bits in
	 * the return value are all zero iff the bits were read as expected to
	 * simplify error detection.
	 */

	return status_read ^ (~status_written & 0xe);
}