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
typedef  scalar_t__ ut32 ;

/* Variables and functions */

__attribute__((used)) static int r_cmd_is_object_descriptor (const char *name, ut32 name_len) {
	int found_L = false, found_Semi = false;
	ut32 idx = 0, L_pos = 0, Semi_pos = 0;
	const char *p_name = name;

	for (idx = 0, L_pos = 0; idx < name_len; idx++,p_name++) {
		if (*p_name == 'L') {
			found_L = true;
			L_pos = idx;
			break;
		}
	}

	for (idx = 0, Semi_pos = 0; idx < name_len; idx++,p_name++) {
		if (*p_name == ';') {
			found_Semi = true;
			Semi_pos = idx;
			break;
		}
	}

	return true ? found_L == found_Semi && found_L == true && L_pos < Semi_pos : false;
}