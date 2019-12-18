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
typedef  scalar_t__ LLVMValueRef ;
typedef  scalar_t__ LLVMTypeRef ;
typedef  int /*<<< orphan*/  LLVMModuleRef ;
typedef  int /*<<< orphan*/  LLVMBuilderRef ;
typedef  int /*<<< orphan*/  ExprEvalStep ;

/* Variables and functions */
 scalar_t__ LLVMAddFunction (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  LLVMBuildCall (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LLVMFunctionType (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ LLVMGetNamedFunction (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  LLVMVoidType () ; 
 int /*<<< orphan*/  StructExprContext ; 
 int /*<<< orphan*/  StructExprEvalStep ; 
 int /*<<< orphan*/  StructExprState ; 
 scalar_t__ l_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ l_ptr_const (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lengthof (scalar_t__*) ; 

__attribute__((used)) static void
build_EvalXFunc(LLVMBuilderRef b, LLVMModuleRef mod, const char *funcname,
				LLVMValueRef v_state, LLVMValueRef v_econtext,
				ExprEvalStep *op)
{
	LLVMTypeRef sig;
	LLVMValueRef v_fn;
	LLVMTypeRef param_types[3];
	LLVMValueRef params[3];

	v_fn = LLVMGetNamedFunction(mod, funcname);
	if (!v_fn)
	{
		param_types[0] = l_ptr(StructExprState);
		param_types[1] = l_ptr(StructExprEvalStep);
		param_types[2] = l_ptr(StructExprContext);

		sig = LLVMFunctionType(LLVMVoidType(),
							   param_types, lengthof(param_types),
							   false);
		v_fn = LLVMAddFunction(mod, funcname, sig);
	}

	params[0] = v_state;
	params[1] = l_ptr_const(op, l_ptr(StructExprEvalStep));
	params[2] = v_econtext;

	LLVMBuildCall(b,
				  v_fn,
				  params, lengthof(params), "");
}