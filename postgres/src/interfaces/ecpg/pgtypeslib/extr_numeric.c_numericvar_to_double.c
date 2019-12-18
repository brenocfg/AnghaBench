#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dscale; } ;
typedef  TYPE_1__ numeric ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 scalar_t__ PGTYPES_NUM_BAD_NUMERIC ; 
 scalar_t__ PGTYPES_NUM_OVERFLOW ; 
 scalar_t__ PGTYPES_NUM_UNDERFLOW ; 
 scalar_t__ PGTYPESnumeric_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PGTYPESnumeric_free (TYPE_1__*) ; 
 TYPE_1__* PGTYPESnumeric_new () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_str_from_var (TYPE_1__*,int /*<<< orphan*/ ) ; 
 double strtod (char*,char**) ; 

__attribute__((used)) static int
numericvar_to_double(numeric *var, double *dp)
{
	char	   *tmp;
	double		val;
	char	   *endptr;
	numeric    *varcopy = PGTYPESnumeric_new();

	if (varcopy == NULL)
		return -1;

	if (PGTYPESnumeric_copy(var, varcopy) < 0)
	{
		PGTYPESnumeric_free(varcopy);
		return -1;
	}

	tmp = get_str_from_var(varcopy, varcopy->dscale);
	PGTYPESnumeric_free(varcopy);

	if (tmp == NULL)
		return -1;

	/*
	 * strtod does not reset errno to 0 in case of success.
	 */
	errno = 0;
	val = strtod(tmp, &endptr);
	if (errno == ERANGE)
	{
		free(tmp);
		if (val == 0)
			errno = PGTYPES_NUM_UNDERFLOW;
		else
			errno = PGTYPES_NUM_OVERFLOW;
		return -1;
	}

	/* can't free tmp yet, endptr points still into it */
	if (*endptr != '\0')
	{
		/* shouldn't happen ... */
		free(tmp);
		errno = PGTYPES_NUM_BAD_NUMERIC;
		return -1;
	}
	free(tmp);
	*dp = val;
	return 0;
}