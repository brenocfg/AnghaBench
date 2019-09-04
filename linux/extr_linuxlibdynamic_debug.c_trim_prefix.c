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
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static inline const char *trim_prefix(const char *path)
{
	int skip = strlen(__FILE__) - strlen("lib/dynamic_debug.c");

	if (strncmp(path, __FILE__, skip))
		skip = 0; /* prefix mismatch, don't skip */

	return path + skip;
}