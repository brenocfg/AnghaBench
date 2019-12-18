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
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 double strtod (char const*,char**) ; 
 scalar_t__ unlikely (int) ; 

bool
strtodouble(const char *str, bool errorOK, double *dv)
{
	char	   *end;

	errno = 0;
	*dv = strtod(str, &end);

	if (unlikely(errno != 0))
	{
		if (!errorOK)
			fprintf(stderr,
					"value \"%s\" is out of range for type double\n", str);
		return false;
	}

	if (unlikely(end == str || *end != '\0'))
	{
		if (!errorOK)
			fprintf(stderr,
					"invalid input syntax for type double: \"%s\"\n", str);
		return false;
	}
	return true;
}