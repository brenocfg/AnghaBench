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
 int /*<<< orphan*/  pg_log_error (char*,char const*,char const*) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 scalar_t__ pg_strncasecmp (char const*,char*,size_t) ; 
 size_t strlen (char const*) ; 

bool
ParseVariableBool(const char *value, const char *name, bool *result)
{
	size_t		len;
	bool		valid = true;

	/* Treat "unset" as an empty string, which will lead to error below */
	if (value == NULL)
		value = "";

	len = strlen(value);

	if (len > 0 && pg_strncasecmp(value, "true", len) == 0)
		*result = true;
	else if (len > 0 && pg_strncasecmp(value, "false", len) == 0)
		*result = false;
	else if (len > 0 && pg_strncasecmp(value, "yes", len) == 0)
		*result = true;
	else if (len > 0 && pg_strncasecmp(value, "no", len) == 0)
		*result = false;
	/* 'o' is not unique enough */
	else if (pg_strncasecmp(value, "on", (len > 2 ? len : 2)) == 0)
		*result = true;
	else if (pg_strncasecmp(value, "off", (len > 2 ? len : 2)) == 0)
		*result = false;
	else if (pg_strcasecmp(value, "1") == 0)
		*result = true;
	else if (pg_strcasecmp(value, "0") == 0)
		*result = false;
	else
	{
		/* string is not recognized; don't clobber *result */
		if (name)
			pg_log_error("unrecognized value \"%s\" for \"%s\": Boolean expected",
						 value, name);
		valid = false;
	}
	return valid;
}