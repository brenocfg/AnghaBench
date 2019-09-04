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
 int EINVAL ; 
 unsigned long INT_MAX ; 
 int errno ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_sym_idx(char **inp, int *idx)
{
	*idx = -1;

	*inp += strspn(*inp, " ");

	if (**inp != '#')
		return 0;

	*inp += 1;

	if (**inp == 'g' || **inp == 'G') {
		*inp += 1;
		*idx = 0;
	} else {
		unsigned long num;
		char *endptr;

		errno = 0;
		num = strtoul(*inp, &endptr, 0);
		if (errno)
			return -errno;
		if (endptr == *inp || num > INT_MAX)
			return -EINVAL;
		*inp = endptr;
		*idx = num;
	}

	return 0;
}