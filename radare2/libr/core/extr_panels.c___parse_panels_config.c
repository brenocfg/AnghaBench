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

/* Variables and functions */
 scalar_t__ R_STR_ISEMPTY (char const*) ; 
 char* r_str_newlen (char const*,int) ; 

char *__parse_panels_config(const char *cfg, int len) {
	if (R_STR_ISEMPTY (cfg) || len < 2) {
		return NULL;
	}
	char *tmp = r_str_newlen (cfg, len + 1);
	int i = 0;
	for (; i < len; i++) {
		if (tmp[i] == '}') {
			if (i + 1 < len) {
				if (tmp[i + 1] == ',') {
					tmp[i + 1] = '\n';
				}
				continue;
			}
			tmp[i + 1] = '\n';
		}
	}
	return tmp;
}