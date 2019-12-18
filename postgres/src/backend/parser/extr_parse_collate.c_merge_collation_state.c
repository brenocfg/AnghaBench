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
struct TYPE_3__ {int strength; void* collation; int location; int location2; int /*<<< orphan*/  pstate; void* collation2; } ;
typedef  TYPE_1__ assign_collations_context ;
typedef  void* Oid ;
typedef  int CollateStrength ;

/* Variables and functions */
#define  COLLATE_CONFLICT 131 
#define  COLLATE_EXPLICIT 130 
#define  COLLATE_IMPLICIT 129 
#define  COLLATE_NONE 128 
 void* DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERRCODE_COLLATION_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_collation_name (void*) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
merge_collation_state(Oid collation,
					  CollateStrength strength,
					  int location,
					  Oid collation2,
					  int location2,
					  assign_collations_context *context)
{
	/*
	 * If the collation strength for this node is different from what's
	 * already in *context, then this node either dominates or is dominated by
	 * earlier siblings.
	 */
	if (strength > context->strength)
	{
		/* Override previous parent state */
		context->collation = collation;
		context->strength = strength;
		context->location = location;
		/* Bubble up error info if applicable */
		if (strength == COLLATE_CONFLICT)
		{
			context->collation2 = collation2;
			context->location2 = location2;
		}
	}
	else if (strength == context->strength)
	{
		/* Merge, or detect error if there's a collation conflict */
		switch (strength)
		{
			case COLLATE_NONE:
				/* Nothing + nothing is still nothing */
				break;
			case COLLATE_IMPLICIT:
				if (collation != context->collation)
				{
					/*
					 * Non-default implicit collation always beats default.
					 */
					if (context->collation == DEFAULT_COLLATION_OID)
					{
						/* Override previous parent state */
						context->collation = collation;
						context->strength = strength;
						context->location = location;
					}
					else if (collation != DEFAULT_COLLATION_OID)
					{
						/*
						 * Oops, we have a conflict.  We cannot throw error
						 * here, since the conflict could be resolved by a
						 * later sibling CollateExpr, or the parent might not
						 * care about collation anyway.  Return enough info to
						 * throw the error later, if needed.
						 */
						context->strength = COLLATE_CONFLICT;
						context->collation2 = collation;
						context->location2 = location;
					}
				}
				break;
			case COLLATE_CONFLICT:
				/* We're still conflicted ... */
				break;
			case COLLATE_EXPLICIT:
				if (collation != context->collation)
				{
					/*
					 * Oops, we have a conflict of explicit COLLATE clauses.
					 * Here we choose to throw error immediately; that is what
					 * the SQL standard says to do, and there's no good reason
					 * to be less strict.
					 */
					ereport(ERROR,
							(errcode(ERRCODE_COLLATION_MISMATCH),
							 errmsg("collation mismatch between explicit collations \"%s\" and \"%s\"",
									get_collation_name(context->collation),
									get_collation_name(collation)),
							 parser_errposition(context->pstate, location)));
				}
				break;
		}
	}
}