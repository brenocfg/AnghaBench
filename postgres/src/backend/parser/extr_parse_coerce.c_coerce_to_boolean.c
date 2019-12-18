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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ BOOLOID ; 
 int /*<<< orphan*/  COERCE_IMPLICIT_CAST ; 
 int /*<<< orphan*/  COERCION_ASSIGNMENT ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * coerce_to_target_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  exprLocation (int /*<<< orphan*/ *) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 scalar_t__ expression_returns_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Node *
coerce_to_boolean(ParseState *pstate, Node *node,
				  const char *constructName)
{
	Oid			inputTypeId = exprType(node);

	if (inputTypeId != BOOLOID)
	{
		Node	   *newnode;

		newnode = coerce_to_target_type(pstate, node, inputTypeId,
										BOOLOID, -1,
										COERCION_ASSIGNMENT,
										COERCE_IMPLICIT_CAST,
										-1);
		if (newnode == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
			/* translator: first %s is name of a SQL construct, eg WHERE */
					 errmsg("argument of %s must be type %s, not type %s",
							constructName, "boolean",
							format_type_be(inputTypeId)),
					 parser_errposition(pstate, exprLocation(node))));
		node = newnode;
	}

	if (expression_returns_set(node))
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
		/* translator: %s is name of a SQL construct, eg WHERE */
				 errmsg("argument of %s must not return a set",
						constructName),
				 parser_errposition(pstate, exprLocation(node))));

	return node;
}