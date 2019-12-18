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
 scalar_t__ IFNAMSIZ ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strnlen (char const*,scalar_t__) ; 

bool dev_valid_name(const char *name)
{
	if (*name == '\0')
		return false;
	if (strnlen(name, IFNAMSIZ) == IFNAMSIZ)
		return false;
	if (!strcmp(name, ".") || !strcmp(name, ".."))
		return false;

	while (*name) {
		if (*name == '/' || *name == ':' || isspace(*name))
			return false;
		name++;
	}
	return true;
}