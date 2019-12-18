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
typedef  int /*<<< orphan*/  numeric ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 long LONG_MIN ; 
 scalar_t__ PGTYPES_NUM_OVERFLOW ; 
 scalar_t__ PGTYPES_NUM_UNDERFLOW ; 
 char* PGTYPESnumeric_to_asc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 long strtol (char*,char**,int) ; 

int
PGTYPESnumeric_to_long(numeric *nv, long *lp)
{
	char	   *s = PGTYPESnumeric_to_asc(nv, 0);
	char	   *endptr;

	if (s == NULL)
		return -1;

	errno = 0;
	*lp = strtol(s, &endptr, 10);
	if (endptr == s)
	{
		/* this should not happen actually */
		free(s);
		return -1;
	}
	free(s);
	if (errno == ERANGE)
	{
		if (*lp == LONG_MIN)
			errno = PGTYPES_NUM_UNDERFLOW;
		else
			errno = PGTYPES_NUM_OVERFLOW;
		return -1;
	}
	return 0;
}