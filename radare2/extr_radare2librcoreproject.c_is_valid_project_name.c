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
 scalar_t__ IS_DIGIT (char const) ; 
 scalar_t__ r_str_endswith (char const*,char*) ; 

__attribute__((used)) static bool is_valid_project_name(const char *name) {
	int i;
	if (r_str_endswith (name, ".zip")) {
		return false;
	}
	for (i = 0; name[i]; i++) {
		switch (name[i]) {
		case '\\': // for w32
		case '.':
		case '_':
		case ':':
		case '-':
			continue;
		}
		if (name[i] >= 'a' && name[i] <= 'z') {
			continue;
		}
		if (name[i] >= 'A' && name[i] <= 'Z') {
			continue;
		}
		if (IS_DIGIT (name[i])) {
			continue;
		}
		return false;
	}
	return true;
}