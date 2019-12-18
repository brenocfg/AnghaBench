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
typedef  int ut8 ;

/* Variables and functions */

__attribute__((used)) static inline ut8 arg_bit (ut8 bit_addr) {
	if (bit_addr < 0x80) {
		// bit addresses 0x00-0x7f are mapped to bytes at 0x20-0x2f
		return (bit_addr >> 3) + 0x20;
	}
	// bit addresses 0x80-0xff are mapped to bytes at 0x80, 0x88, 0x98, ...
	return bit_addr & 0xf8;
}