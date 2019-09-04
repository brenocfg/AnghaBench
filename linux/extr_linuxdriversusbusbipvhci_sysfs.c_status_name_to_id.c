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
 int kstrtol (char*,int,long*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int status_name_to_id(const char *name)
{
	char *c;
	long val;
	int ret;

	c = strchr(name, '.');
	if (c == NULL)
		return 0;

	ret = kstrtol(c+1, 10, &val);
	if (ret < 0)
		return ret;

	return val;
}