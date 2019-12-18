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
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void jack_kctl_name_gen(char *name, const char *src_name, int size)
{
	size_t count = strlen(src_name);
	bool need_cat = true;

	/* remove redundant " Jack" from src_name */
	if (count >= 5)
		need_cat = strncmp(&src_name[count - 5], " Jack", 5) ? true : false;

	snprintf(name, size, need_cat ? "%s Jack" : "%s", src_name);

}