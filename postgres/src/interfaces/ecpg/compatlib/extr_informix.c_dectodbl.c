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
typedef  int /*<<< orphan*/  decimal ;

/* Variables and functions */
 int ECPG_INFORMIX_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  PGTYPESnumeric_free (int /*<<< orphan*/ *) ; 
 scalar_t__ PGTYPESnumeric_from_decimal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PGTYPESnumeric_new () ; 
 int PGTYPESnumeric_to_double (int /*<<< orphan*/ *,double*) ; 

int
dectodbl(decimal *np, double *dblp)
{
	int			i;
	numeric    *nres = PGTYPESnumeric_new();

	if (nres == NULL)
		return ECPG_INFORMIX_OUT_OF_MEMORY;

	if (PGTYPESnumeric_from_decimal(np, nres) != 0)
	{
		PGTYPESnumeric_free(nres);
		return ECPG_INFORMIX_OUT_OF_MEMORY;
	}

	i = PGTYPESnumeric_to_double(nres, dblp);
	PGTYPESnumeric_free(nres);

	return i;
}