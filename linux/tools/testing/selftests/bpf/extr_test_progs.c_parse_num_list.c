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
struct test_selector {int* num_set; int num_set_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int errno ; 
 int /*<<< orphan*/  free (int*) ; 
 int* realloc (int*,int) ; 
 int strtol (char const*,char**,int) ; 

int parse_num_list(const char *s, struct test_selector *sel)
{
	int i, set_len = 0, num, start = 0, end = -1;
	bool *set = NULL, *tmp, parsing_end = false;
	char *next;

	while (s[0]) {
		errno = 0;
		num = strtol(s, &next, 10);
		if (errno)
			return -errno;

		if (parsing_end)
			end = num;
		else
			start = num;

		if (!parsing_end && *next == '-') {
			s = next + 1;
			parsing_end = true;
			continue;
		} else if (*next == ',') {
			parsing_end = false;
			s = next + 1;
			end = num;
		} else if (*next == '\0') {
			parsing_end = false;
			s = next;
			end = num;
		} else {
			return -EINVAL;
		}

		if (start > end)
			return -EINVAL;

		if (end + 1 > set_len) {
			set_len = end + 1;
			tmp = realloc(set, set_len);
			if (!tmp) {
				free(set);
				return -ENOMEM;
			}
			set = tmp;
		}
		for (i = start; i <= end; i++) {
			set[i] = true;
		}

	}

	if (!set)
		return -EINVAL;

	sel->num_set = set;
	sel->num_set_len = set_len;

	return 0;
}