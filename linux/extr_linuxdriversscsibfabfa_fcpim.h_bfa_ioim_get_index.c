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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long BFA_IOBUCKET_MAX ; 

__attribute__((used)) static inline u32
bfa_ioim_get_index(u32 n) {
	int pos = 0;
	if (n >= (1UL)<<22)
		return BFA_IOBUCKET_MAX - 1;
	n >>= 8;
	if (n >= (1UL)<<16) {
		n >>= 16;
		pos += 16;
	}
	if (n >= 1 << 8) {
		n >>= 8;
		pos += 8;
	}
	if (n >= 1 << 4) {
		n >>= 4;
		pos += 4;
	}
	if (n >= 1 << 2) {
		n >>= 2;
		pos += 2;
	}
	if (n >= 1 << 1)
		pos += 1;

	return (n == 0) ? (0) : pos;
}