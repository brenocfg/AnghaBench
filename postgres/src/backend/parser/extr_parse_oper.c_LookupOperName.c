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

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpernameGetOprid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_signature_string (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int) ; 

Oid
LookupOperName(ParseState *pstate, List *opername, Oid oprleft, Oid oprright,
			   bool noError, int location)
{
	Oid			result;

	result = OpernameGetOprid(opername, oprleft, oprright);
	if (OidIsValid(result))
		return result;

	/* we don't use op_error here because only an exact match is wanted */
	if (!noError)
	{
		char		oprkind;

		if (!OidIsValid(oprleft))
			oprkind = 'l';
		else if (!OidIsValid(oprright))
			oprkind = 'r';
		else
			oprkind = 'b';

		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("operator does not exist: %s",
						op_signature_string(opername, oprkind,
											oprleft, oprright)),
				 parser_errposition(pstate, location)));
	}

	return InvalidOid;
}