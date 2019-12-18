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
 scalar_t__ IS_HIGHBIT_SET (unsigned char const) ; 
 int /*<<< orphan*/ * strchr (char*,unsigned char const) ; 

__attribute__((used)) static bool
valid_variable_name(const char *name)
{
	const unsigned char *ptr = (const unsigned char *) name;

	/* Mustn't be zero-length */
	if (*ptr == '\0')
		return false;

	while (*ptr)
	{
		if (IS_HIGHBIT_SET(*ptr) ||
			strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz"
				   "_0123456789", *ptr) != NULL)
			ptr++;
		else
			return false;
	}

	return true;
}