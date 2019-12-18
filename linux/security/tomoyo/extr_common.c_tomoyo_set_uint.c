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
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned int*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static void tomoyo_set_uint(unsigned int *i, const char *string,
			    const char *find)
{
	const char *cp = strstr(string, find);

	if (cp)
		sscanf(cp + strlen(find), "=%u", i);
}