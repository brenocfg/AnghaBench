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
 int /*<<< orphan*/  CDECIMALTYPE ; 
 int /*<<< orphan*/  CINTTYPE ; 
 int ECPG_INFORMIX_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  PGTYPESnumeric_free (int /*<<< orphan*/ *) ; 
 int PGTYPESnumeric_from_int (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PGTYPESnumeric_new () ; 
 int PGTYPESnumeric_to_decimal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ risnull (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsetnull (int /*<<< orphan*/ ,char*) ; 

int
deccvint(int in, decimal *np)
{
	numeric    *nres;
	int			result = 1;

	rsetnull(CDECIMALTYPE, (char *) np);
	if (risnull(CINTTYPE, (char *) &in))
		return 0;

	nres = PGTYPESnumeric_new();
	if (nres == NULL)
		return ECPG_INFORMIX_OUT_OF_MEMORY;

	result = PGTYPESnumeric_from_int(in, nres);
	if (result == 0)
		result = PGTYPESnumeric_to_decimal(nres, np);

	PGTYPESnumeric_free(nres);
	return result;
}