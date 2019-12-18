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
typedef  scalar_t__ ut64 ;
typedef  int ut32 ;

/* Variables and functions */

__attribute__((used)) static inline ut64 xtensa_imm18s (ut64 addr, const ut8 *buf) {
	ut32 offset = (buf[0] >> 6) | (((ut32)buf[1]) << 2) | (((ut32)buf[2]) << 10);
	if (offset & 0x20000) {
		return addr + 4 + offset - 0x40000;
	}
	return addr + 4 + offset;
}