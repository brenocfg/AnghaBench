#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_11__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_2__ eval_const_expressions_context ;
struct TYPE_14__ {int /*<<< orphan*/  prosupport; int /*<<< orphan*/  proretset; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int funcvariadic; int location; int /*<<< orphan*/ * args; void* inputcollid; void* funccollid; int /*<<< orphan*/  funcformat; int /*<<< orphan*/  funcretset; void* funcresulttype; void* funcid; TYPE_1__ xpr; } ;
struct TYPE_12__ {TYPE_4__* fcall; int /*<<< orphan*/  root; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ SupportRequestSimplify ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__ FuncExpr ;
typedef  TYPE_5__* Form_pg_proc ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COERCE_EXPLICIT_CALL ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_FuncExpr ; 
 int /*<<< orphan*/  T_SupportRequestSimplify ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  eval_const_expressions_mutator ; 
 int /*<<< orphan*/ * evaluate_function (void*,void*,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * expand_function_arguments (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ expression_tree_mutator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * inline_function (void*,void*,void*,void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static Expr *
simplify_function(Oid funcid, Oid result_type, int32 result_typmod,
				  Oid result_collid, Oid input_collid, List **args_p,
				  bool funcvariadic, bool process_args, bool allow_non_const,
				  eval_const_expressions_context *context)
{
	List	   *args = *args_p;
	HeapTuple	func_tuple;
	Form_pg_proc func_form;
	Expr	   *newexpr;

	/*
	 * We have three strategies for simplification: execute the function to
	 * deliver a constant result, use a transform function to generate a
	 * substitute node tree, or expand in-line the body of the function
	 * definition (which only works for simple SQL-language functions, but
	 * that is a common case).  Each case needs access to the function's
	 * pg_proc tuple, so fetch it just once.
	 *
	 * Note: the allow_non_const flag suppresses both the second and third
	 * strategies; so if !allow_non_const, simplify_function can only return a
	 * Const or NULL.  Argument-list rewriting happens anyway, though.
	 */
	func_tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcid));
	if (!HeapTupleIsValid(func_tuple))
		elog(ERROR, "cache lookup failed for function %u", funcid);
	func_form = (Form_pg_proc) GETSTRUCT(func_tuple);

	/*
	 * Process the function arguments, unless the caller did it already.
	 *
	 * Here we must deal with named or defaulted arguments, and then
	 * recursively apply eval_const_expressions to the whole argument list.
	 */
	if (process_args)
	{
		args = expand_function_arguments(args, result_type, func_tuple);
		args = (List *) expression_tree_mutator((Node *) args,
												eval_const_expressions_mutator,
												(void *) context);
		/* Argument processing done, give it back to the caller */
		*args_p = args;
	}

	/* Now attempt simplification of the function call proper. */

	newexpr = evaluate_function(funcid, result_type, result_typmod,
								result_collid, input_collid,
								args, funcvariadic,
								func_tuple, context);

	if (!newexpr && allow_non_const && OidIsValid(func_form->prosupport))
	{
		/*
		 * Build a SupportRequestSimplify node to pass to the support
		 * function, pointing to a dummy FuncExpr node containing the
		 * simplified arg list.  We use this approach to present a uniform
		 * interface to the support function regardless of how the target
		 * function is actually being invoked.
		 */
		SupportRequestSimplify req;
		FuncExpr	fexpr;

		fexpr.xpr.type = T_FuncExpr;
		fexpr.funcid = funcid;
		fexpr.funcresulttype = result_type;
		fexpr.funcretset = func_form->proretset;
		fexpr.funcvariadic = funcvariadic;
		fexpr.funcformat = COERCE_EXPLICIT_CALL;
		fexpr.funccollid = result_collid;
		fexpr.inputcollid = input_collid;
		fexpr.args = args;
		fexpr.location = -1;

		req.type = T_SupportRequestSimplify;
		req.root = context->root;
		req.fcall = &fexpr;

		newexpr = (Expr *)
			DatumGetPointer(OidFunctionCall1(func_form->prosupport,
											 PointerGetDatum(&req)));

		/* catch a possible API misunderstanding */
		Assert(newexpr != (Expr *) &fexpr);
	}

	if (!newexpr && allow_non_const)
		newexpr = inline_function(funcid, result_type, result_collid,
								  input_collid, args, funcvariadic,
								  func_tuple, context);

	ReleaseSysCache(func_tuple);

	return newexpr;
}