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
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ FuncDetailCode ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_AMBIGUOUS_FUNCTION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FUNCDETAIL_MULTIPLE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_signature_string (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
op_error(ParseState *pstate, List *op, char oprkind,
		 Oid arg1, Oid arg2,
		 FuncDetailCode fdresult, int location)
{
	if (fdresult == FUNCDETAIL_MULTIPLE)
		ereport(ERROR,
				(errcode(ERRCODE_AMBIGUOUS_FUNCTION),
				 errmsg("operator is not unique: %s",
						op_signature_string(op, oprkind, arg1, arg2)),
				 errhint("Could not choose a best candidate operator. "
						 "You might need to add explicit type casts."),
				 parser_errposition(pstate, location)));
	else
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("operator does not exist: %s",
						op_signature_string(op, oprkind, arg1, arg2)),
				 (!arg1 || !arg2) ?
				 errhint("No operator matches the given name and argument type. "
						 "You might need to add an explicit type cast.") :
				 errhint("No operator matches the given name and argument types. "
						 "You might need to add explicit type casts."),
				 parser_errposition(pstate, location)));
}