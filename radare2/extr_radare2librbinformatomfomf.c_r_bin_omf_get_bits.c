#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut32 ;
struct TYPE_5__ {scalar_t__ nb_section; TYPE_1__** sections; } ;
typedef  TYPE_2__ r_bin_omf_obj ;
struct TYPE_4__ {int bits; } ;

/* Variables and functions */

int r_bin_omf_get_bits(r_bin_omf_obj *obj) {
	ut32 ct_sec = 0;
	if (!obj) {
		return 32;
	}

	// we assume if one segdef define a 32 segment all opcodes are 32bits
	while (ct_sec < obj->nb_section) {
		if (obj->sections[ct_sec++]->bits == 32) {
			return 32;
		}
	}
	return 16;
}