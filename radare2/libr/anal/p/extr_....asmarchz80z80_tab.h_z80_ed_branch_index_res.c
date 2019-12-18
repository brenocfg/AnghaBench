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

__attribute__((used)) static ut8 z80_ed_branch_index_res (ut8 hex) {
	if (hex > 0x3f && 0x4c > hex)
		return hex-0x40;
	if (hex == 0x4d)
		return 0xc;
	if (hex > 0x4d && 0x54 > hex)
		return hex-0x42;
	if (hex > 0x55 && 0x5c > hex)
		return hex-0x44;
	if (hex > 0x5d && 0x63 > hex)
		return hex-0x46;
	if (hex > 0x66 && 0x6b > hex)
		return hex-0x4a;
	if (hex > 0x6e && 0x74 > hex)
		return hex-0x4e;
	if (hex > 0x77 && 0x7c > hex)
		return hex-0x52;
	if (hex > 0x9f && 0xa4 > hex)
		return hex-0x76;
	if (hex > 0xa7 && 0xac > hex)
		return hex-0x7a;
	if (hex > 0xaf && 0xb4 > hex)
		return hex-0x7e;
	if (hex > 0xb7 && 0xbc > hex)
		return hex-0x82;
	return 0x3b;
}