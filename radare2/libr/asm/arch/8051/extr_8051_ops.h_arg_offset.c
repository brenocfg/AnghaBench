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
typedef  scalar_t__ ut16 ;

/* Variables and functions */

__attribute__((used)) static inline ut16 arg_offset (ut16 pc, ut8 offset) {
	if (offset < 0x80) {
		return pc + offset;
	}
	offset = 0 - offset;
	return pc - offset;
}