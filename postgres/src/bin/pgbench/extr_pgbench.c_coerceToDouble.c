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
struct TYPE_5__ {double dval; scalar_t__ ival; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ PgBenchValue ;

/* Variables and functions */
 scalar_t__ PGBT_DOUBLE ; 
 scalar_t__ PGBT_INT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* valueTypeName (TYPE_2__*) ; 

__attribute__((used)) static bool
coerceToDouble(PgBenchValue *pval, double *dval)
{
	if (pval->type == PGBT_DOUBLE)
	{
		*dval = pval->u.dval;
		return true;
	}
	else if (pval->type == PGBT_INT)
	{
		*dval = (double) pval->u.ival;
		return true;
	}
	else						/* BOOLEAN or NULL */
	{
		fprintf(stderr, "cannot coerce %s to double\n", valueTypeName(pval));
		return false;
	}
}