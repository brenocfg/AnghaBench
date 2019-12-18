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
 int PATH_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int strscpy (char*,char const*,int) ; 

int copy_path_name(char *dst, const char *src)
{
	int name_len;

	/*
	 * PATH_MAX includes nul, so if strlen(src) >= PATH_MAX it
	 * will truncate and strlen(dst) will be PATH_MAX-1
	 */
	name_len = strscpy(dst, src, PATH_MAX);
	if (WARN_ON_ONCE(name_len < 0))
		name_len = PATH_MAX-1;

	/* we count the trailing nul */
	name_len++;
	return name_len;
}