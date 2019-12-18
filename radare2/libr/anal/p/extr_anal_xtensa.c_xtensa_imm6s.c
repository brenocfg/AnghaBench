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

/* Variables and functions */

__attribute__((used)) static inline ut64 xtensa_imm6s (ut64 addr, const ut8 *buf) {
	ut8 imm6 = (buf[1] >> 4) | (buf[0] & 0x30);
	return (addr + 4 + imm6);
}