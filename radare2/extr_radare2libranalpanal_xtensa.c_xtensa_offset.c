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
typedef  int ut64 ;
typedef  int ut32 ;

/* Variables and functions */

__attribute__((used)) static inline ut64 xtensa_offset (ut64 addr, const ut8 *buf) {
	ut32 offset = ((buf[0] >> 4) & 0xc) | (((ut32)buf[1]) << 4) | (((ut32)buf[2]) << 12);
	if (offset & 0x80000) {
		return (addr + 4 + offset - 0x100000) & ~3;
	}
	return (addr + 4 + offset) & ~3;
}