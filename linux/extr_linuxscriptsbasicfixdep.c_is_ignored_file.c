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
 scalar_t__ str_ends_with (char const*,int,char*) ; 

__attribute__((used)) static int is_ignored_file(const char *s, int len)
{
	return str_ends_with(s, len, "include/generated/autoconf.h") ||
	       str_ends_with(s, len, "include/generated/autoksyms.h") ||
	       str_ends_with(s, len, ".ver");
}