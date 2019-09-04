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

__attribute__((used)) static ut8 z80_op_24_branch_index_res (ut8 hex) {
	if (hex < 0x40) {
		return hex;
	}
	switch (hex) {
	case 0x46: return 0x40;
	case 0x4e: return 0x41;
	case 0x56: return 0x42;
	case 0x5e: return 0x43;
	case 0x66: return 0x44;
	case 0x6e: return 0x45;
	case 0x76: return 0x46;
	case 0x7e: return 0x47;
	}
	return (hex > 0x7f)? hex - 0x38: 0xc8;
}