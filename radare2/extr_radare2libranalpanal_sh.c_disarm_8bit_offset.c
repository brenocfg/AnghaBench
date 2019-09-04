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
typedef  int ut64 ;
typedef  int ut32 ;

/* Variables and functions */

__attribute__((used)) static ut64 disarm_8bit_offset (ut64 pc, ut32 offs) {
		/* pc (really, op->addr) is 64 bits, so we need to sign-extend
		 * to 64 bits instead of the 32 the actual CPU does */
		ut64 off = offs;
	/* sign extend if higher bit is 1 (0x08) */
	if ((off & 0x80) == 0x80)
	{
		off |= ~0xFF;
	}
	return (off << 1) + pc + 4;
}