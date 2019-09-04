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
 int /*<<< orphan*/  isxdigit (char const) ; 
 scalar_t__ r_str_startswith (char const*,char*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int) ; 

int read_thread_id(const char *src, int *pid, int *tid, bool multiprocess) {
	char *ptr1;
	if (multiprocess && *src == 'p') {
		src++;
		if (!(ptr1 = strchr (src, '.'))) {
			return -1;
		}
		ptr1++;
		if (r_str_startswith (src, "-1")) {
			if (r_str_startswith (ptr1, "-1")) {
				*pid = *tid = -1;
				return 0;
			}
			return -1;
		}
		if (!isxdigit (*src)) {
			return -1;
		}
		if (r_str_startswith (ptr1, "-1")) {
			*pid = (int) strtol (src, NULL, 16);
			*tid = -1;
			return 0;
		}
		if (!isxdigit (*ptr1)) {
			return -1;
		}
		*pid = (int) strtol (src, NULL, 16);
		*tid = (int) strtol (ptr1, NULL, 16);
		return 0;
	}
	if (r_str_startswith (src, "-1")) {
		*tid = -1;
		return 0;
	}
	if (!isxdigit (*src)) {
		return -1;
	}
	*pid = *tid = (int) strtol (src, NULL, 16);
	return 0;
}