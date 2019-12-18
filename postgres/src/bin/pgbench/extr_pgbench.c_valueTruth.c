#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bval; double dval; int /*<<< orphan*/  ival; } ;
struct TYPE_5__ {int type; TYPE_1__ u; } ;
typedef  TYPE_2__ PgBenchValue ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
#define  PGBT_BOOLEAN 131 
#define  PGBT_DOUBLE 130 
#define  PGBT_INT 129 
#define  PGBT_NULL 128 

__attribute__((used)) static bool
valueTruth(PgBenchValue *pval)
{
	switch (pval->type)
	{
		case PGBT_NULL:
			return false;
		case PGBT_BOOLEAN:
			return pval->u.bval;
		case PGBT_INT:
			return pval->u.ival != 0;
		case PGBT_DOUBLE:
			return pval->u.dval != 0.0;
		default:
			/* internal error, unexpected type */
			Assert(0);
			return false;
	}
}