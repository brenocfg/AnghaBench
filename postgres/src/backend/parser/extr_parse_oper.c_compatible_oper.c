#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  oprright; int /*<<< orphan*/  oprleft; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  scalar_t__ Operator ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__* Form_pg_operator ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (scalar_t__) ; 
 scalar_t__ IsBinaryCoercible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_signature_string (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ oper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int) ; 

Operator
compatible_oper(ParseState *pstate, List *op, Oid arg1, Oid arg2,
				bool noError, int location)
{
	Operator	optup;
	Form_pg_operator opform;

	/* oper() will find the best available match */
	optup = oper(pstate, op, arg1, arg2, noError, location);
	if (optup == (Operator) NULL)
		return (Operator) NULL; /* must be noError case */

	/* but is it good enough? */
	opform = (Form_pg_operator) GETSTRUCT(optup);
	if (IsBinaryCoercible(arg1, opform->oprleft) &&
		IsBinaryCoercible(arg2, opform->oprright))
		return optup;

	/* nope... */
	ReleaseSysCache(optup);

	if (!noError)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("operator requires run-time type coercion: %s",
						op_signature_string(op, 'b', arg1, arg2)),
				 parser_errposition(pstate, location)));

	return (Operator) NULL;
}