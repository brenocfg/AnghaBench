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
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  read_obj (char const*) ; 
 char* strdup (char*) ; 
 unsigned long strtoul (int /*<<< orphan*/ ,char**,int) ; 

__attribute__((used)) static unsigned long get_obj_and_str(const char *name, char **x)
{
	unsigned long result = 0;
	char *p;

	*x = NULL;

	if (!read_obj(name)) {
		x = NULL;
		return 0;
	}
	result = strtoul(buffer, &p, 10);
	while (*p == ' ')
		p++;
	if (*p)
		*x = strdup(p);
	return result;
}