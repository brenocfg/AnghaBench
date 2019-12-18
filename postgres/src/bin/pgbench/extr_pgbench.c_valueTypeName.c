#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ PgBenchValue ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ PGBT_BOOLEAN ; 
 scalar_t__ PGBT_DOUBLE ; 
 scalar_t__ PGBT_INT ; 
 scalar_t__ PGBT_NO_VALUE ; 
 scalar_t__ PGBT_NULL ; 

__attribute__((used)) static char *
valueTypeName(PgBenchValue *pval)
{
	if (pval->type == PGBT_NO_VALUE)
		return "none";
	else if (pval->type == PGBT_NULL)
		return "null";
	else if (pval->type == PGBT_INT)
		return "int";
	else if (pval->type == PGBT_DOUBLE)
		return "double";
	else if (pval->type == PGBT_BOOLEAN)
		return "boolean";
	else
	{
		/* internal error, should never get there */
		Assert(false);
		return NULL;
	}
}