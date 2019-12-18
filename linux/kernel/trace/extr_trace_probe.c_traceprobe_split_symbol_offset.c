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
 int kstrtol (char*,int /*<<< orphan*/ ,long*) ; 
 char* strpbrk (char*,char*) ; 

int traceprobe_split_symbol_offset(char *symbol, long *offset)
{
	char *tmp;
	int ret;

	if (!offset)
		return -EINVAL;

	tmp = strpbrk(symbol, "+-");
	if (tmp) {
		ret = kstrtol(tmp, 0, offset);
		if (ret)
			return ret;
		*tmp = '\0';
	} else
		*offset = 0;

	return 0;
}