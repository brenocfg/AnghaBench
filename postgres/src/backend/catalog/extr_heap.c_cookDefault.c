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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COERCE_IMPLICIT_CAST ; 
 int /*<<< orphan*/  COERCION_ASSIGNMENT ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXPR_KIND_COLUMN_DEFAULT ; 
 int /*<<< orphan*/  EXPR_KIND_GENERATED_COLUMN ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_expr_collations (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_nested_generated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * coerce_to_target_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ contain_mutable_functions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  contain_var_clause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transformExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Node *
cookDefault(ParseState *pstate,
			Node *raw_default,
			Oid atttypid,
			int32 atttypmod,
			const char *attname,
			char attgenerated)
{
	Node	   *expr;

	Assert(raw_default != NULL);

	/*
	 * Transform raw parsetree to executable expression.
	 */
	expr = transformExpr(pstate, raw_default, attgenerated ? EXPR_KIND_GENERATED_COLUMN : EXPR_KIND_COLUMN_DEFAULT);

	if (attgenerated)
	{
		check_nested_generated(pstate, expr);

		if (contain_mutable_functions(expr))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("generation expression is not immutable")));
	}
	else
	{
		/*
		 * For a default expression, transformExpr() should have rejected
		 * column references.
		 */
		Assert(!contain_var_clause(expr));
	}

	/*
	 * Coerce the expression to the correct type and typmod, if given. This
	 * should match the parser's processing of non-defaulted expressions ---
	 * see transformAssignedExpr().
	 */
	if (OidIsValid(atttypid))
	{
		Oid			type_id = exprType(expr);

		expr = coerce_to_target_type(pstate, expr, type_id,
									 atttypid, atttypmod,
									 COERCION_ASSIGNMENT,
									 COERCE_IMPLICIT_CAST,
									 -1);
		if (expr == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("column \"%s\" is of type %s"
							" but default expression is of type %s",
							attname,
							format_type_be(atttypid),
							format_type_be(type_id)),
					 errhint("You will need to rewrite or cast the expression.")));
	}

	/*
	 * Finally, take care of collations in the finished expression.
	 */
	assign_expr_collations(pstate, expr);

	return expr;
}