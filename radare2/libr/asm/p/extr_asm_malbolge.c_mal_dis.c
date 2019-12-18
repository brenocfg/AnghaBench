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
typedef  int const ut64 ;

/* Variables and functions */

__attribute__((used)) static const char *mal_dis(ut64 c, const ut8 *buf, ut64 len) {
	if (len) {
		switch ((buf[0] + c) % 94) {
		case 4: return "jmp [d]";
		case 5: return "out a";
		case 23: return "in a";
		case 39: return "rotr [d], mov a, [d]";
		case 40: return "mov d, [d]";
		case 62: return "crz [d], a, mov a, [d]";
		case 81: return "end";
		default: return "nop";
		}
	}
	return NULL;
}