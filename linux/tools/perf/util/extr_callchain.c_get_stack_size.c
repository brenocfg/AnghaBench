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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,char const*) ; 
 unsigned long round_down (int /*<<< orphan*/ ,int) ; 
 unsigned long round_up (unsigned long,int) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_stack_size(const char *str, unsigned long *_size)
{
	char *endptr;
	unsigned long size;
	unsigned long max_size = round_down(USHRT_MAX, sizeof(u64));

	size = strtoul(str, &endptr, 0);

	do {
		if (*endptr)
			break;

		size = round_up(size, sizeof(u64));
		if (!size || size > max_size)
			break;

		*_size = size;
		return 0;

	} while (0);

	pr_err("callchain: Incorrect stack dump size (max %ld): %s\n",
	       max_size, str);
	return -1;
}