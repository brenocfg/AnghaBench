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
struct TYPE_8__ {int dscale; } ;
typedef  TYPE_1__ numeric ;

/* Variables and functions */
 scalar_t__ PGTYPESnumeric_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PGTYPESnumeric_free (TYPE_1__*) ; 
 TYPE_1__* PGTYPESnumeric_new () ; 
 char* get_str_from_var (TYPE_1__*,int) ; 

char *
PGTYPESnumeric_to_asc(numeric *num, int dscale)
{
	numeric    *numcopy = PGTYPESnumeric_new();
	char	   *s;

	if (numcopy == NULL)
		return NULL;

	if (PGTYPESnumeric_copy(num, numcopy) < 0)
	{
		PGTYPESnumeric_free(numcopy);
		return NULL;
	}

	if (dscale < 0)
		dscale = num->dscale;

	/* get_str_from_var may change its argument */
	s = get_str_from_var(numcopy, dscale);
	PGTYPESnumeric_free(numcopy);
	return s;
}