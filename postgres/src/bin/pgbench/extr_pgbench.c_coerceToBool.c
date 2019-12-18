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
struct TYPE_5__ {int bval; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ PgBenchValue ;

/* Variables and functions */
 scalar_t__ PGBT_BOOLEAN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* valueTypeName (TYPE_2__*) ; 

__attribute__((used)) static bool
coerceToBool(PgBenchValue *pval, bool *bval)
{
	if (pval->type == PGBT_BOOLEAN)
	{
		*bval = pval->u.bval;
		return true;
	}
	else						/* NULL, INT or DOUBLE */
	{
		fprintf(stderr, "cannot coerce %s to boolean\n", valueTypeName(pval));
		*bval = false;			/* suppress uninitialized-variable warnings */
		return false;
	}
}