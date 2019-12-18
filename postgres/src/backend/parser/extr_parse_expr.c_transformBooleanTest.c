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
struct TYPE_3__ {int booltesttype; int /*<<< orphan*/ * arg; int /*<<< orphan*/  location; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_1__ BooleanTest ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  IS_FALSE 133 
#define  IS_NOT_FALSE 132 
#define  IS_NOT_TRUE 131 
#define  IS_NOT_UNKNOWN 130 
#define  IS_TRUE 129 
#define  IS_UNKNOWN 128 
 int /*<<< orphan*/  PREC_GROUP_POSTFIX_IS ; 
 scalar_t__ coerce_to_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  emit_precedence_warnings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ operator_precedence_warning ; 
 scalar_t__ transformExprRecurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *
transformBooleanTest(ParseState *pstate, BooleanTest *b)
{
	const char *clausename;

	if (operator_precedence_warning)
		emit_precedence_warnings(pstate, PREC_GROUP_POSTFIX_IS, "IS",
								 (Node *) b->arg, NULL,
								 b->location);

	switch (b->booltesttype)
	{
		case IS_TRUE:
			clausename = "IS TRUE";
			break;
		case IS_NOT_TRUE:
			clausename = "IS NOT TRUE";
			break;
		case IS_FALSE:
			clausename = "IS FALSE";
			break;
		case IS_NOT_FALSE:
			clausename = "IS NOT FALSE";
			break;
		case IS_UNKNOWN:
			clausename = "IS UNKNOWN";
			break;
		case IS_NOT_UNKNOWN:
			clausename = "IS NOT UNKNOWN";
			break;
		default:
			elog(ERROR, "unrecognized booltesttype: %d",
				 (int) b->booltesttype);
			clausename = NULL;	/* keep compiler quiet */
	}

	b->arg = (Expr *) transformExprRecurse(pstate, (Node *) b->arg);

	b->arg = (Expr *) coerce_to_boolean(pstate,
										(Node *) b->arg,
										clausename);

	return (Node *) b;
}