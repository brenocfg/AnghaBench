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
 int ENAMETOOLONG ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 unsigned int strnlen (char const*,unsigned int) ; 

int xt_check_proc_name(const char *name, unsigned int size)
{
	if (name[0] == '\0')
		return -EINVAL;

	if (strnlen(name, size) == size)
		return -ENAMETOOLONG;

	if (strcmp(name, ".") == 0 ||
	    strcmp(name, "..") == 0 ||
	    strchr(name, '/'))
		return -EINVAL;

	return 0;
}