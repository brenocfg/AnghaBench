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
 int kstrtoul (char*,int,unsigned long*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int get_next_ulong(char **str_p, unsigned long *val, char *sep, int base)
{
	char *p_val;

	if (!str_p || !(*str_p))
		return -EINVAL;

	p_val = strsep(str_p, sep);

	if (!p_val)
		return -EINVAL;

	return kstrtoul(p_val, base, val);
}