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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void set_pending_timer_val(int *val, u32 us)
{
	u8 mult = 0;
	u8 shift = 0;

	if (us >= 0x3f) {
		mult = 1; /* mult with 4 */
		shift = 2;
	}
	if (us >= 0x3f * 4) {
		mult = 2; /* mult with 16 */
		shift = 4;
	}
	if (us >= 0x3f * 16) {
		mult = 3; /* mult with 64 */
		shift = 6;
	}

	*val = (mult << 6) | ((us >> shift) & 0x3f);
}