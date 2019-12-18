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
 int ERANGE ; 
 int errno ; 
 scalar_t__ isinf (float) ; 
 double strtod (char const*,char**) ; 

float
strtof(const char *nptr, char **endptr)
{
	int			caller_errno = errno;
	double		dresult;
	float		fresult;

	errno = 0;
	dresult = strtod(nptr, endptr);
	fresult = (float) dresult;

	if (errno == 0)
	{
		/*
		 * Value might be in-range for double but not float.
		 */
		if (dresult != 0 && fresult == 0)
			caller_errno = ERANGE;	/* underflow */
		if (!isinf(dresult) && isinf(fresult))
			caller_errno = ERANGE;	/* overflow */
	}
	else
		caller_errno = errno;

	errno = caller_errno;
	return fresult;
}