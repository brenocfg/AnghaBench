#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_5__ {int /*<<< orphan*/  dval; scalar_t__ ival; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ PgBenchValue ;

/* Variables and functions */
 int /*<<< orphan*/  FLOAT8_FITS_IN_INT64 (double) ; 
 scalar_t__ PGBT_DOUBLE ; 
 scalar_t__ PGBT_INT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isnan (double) ; 
 double rint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* valueTypeName (TYPE_2__*) ; 

__attribute__((used)) static bool
coerceToInt(PgBenchValue *pval, int64 *ival)
{
	if (pval->type == PGBT_INT)
	{
		*ival = pval->u.ival;
		return true;
	}
	else if (pval->type == PGBT_DOUBLE)
	{
		double		dval = rint(pval->u.dval);

		if (isnan(dval) || !FLOAT8_FITS_IN_INT64(dval))
		{
			fprintf(stderr, "double to int overflow for %f\n", dval);
			return false;
		}
		*ival = (int64) dval;
		return true;
	}
	else						/* BOOLEAN or NULL */
	{
		fprintf(stderr, "cannot coerce %s to int\n", valueTypeName(pval));
		return false;
	}
}