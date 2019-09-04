#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int build; int sp; int bits; } ;
typedef  TYPE_1__ Profile ;

/* Variables and functions */
 TYPE_1__** p_table ; 

Profile *windbg_get_profile(int bits, int build, int sp) {
	int i;
	for (i = 0; p_table[i]; i++) {
		if (p_table[i]->build != build) {
			continue;
		}
		if (p_table[i]->sp != sp) {
			continue;
		}
		if (p_table[i]->bits != bits) {
			continue;
		}
		return p_table[i];
	}
	return NULL;
}