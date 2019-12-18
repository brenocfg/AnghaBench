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
struct TYPE_5__ {TYPE_1__* flinfo; } ;
struct TYPE_4__ {char* fn_oid; int /*<<< orphan*/  fn_addr; } ;
typedef  scalar_t__ LLVMValueRef ;
typedef  int /*<<< orphan*/  LLVMModuleRef ;
typedef  int /*<<< orphan*/  LLVMJitContext ;
typedef  int /*<<< orphan*/  LLVMBuilderRef ;
typedef  TYPE_2__* FunctionCallInfo ;

/* Variables and functions */
 scalar_t__ LLVMAddFunction (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ LLVMAddGlobal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LLVMBuildLoad (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  LLVMGetElementType (int /*<<< orphan*/ ) ; 
 scalar_t__ LLVMGetNamedFunction (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LLVMGetNamedGlobal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LLVMSetGlobalConstant (scalar_t__,int) ; 
 int /*<<< orphan*/  LLVMSetInitializer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TypePGFunction ; 
 int /*<<< orphan*/  fmgr_symbol (char*,char**,char**) ; 
 scalar_t__ l_ptr_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* psprintf (char*,char*,...) ; 

LLVMValueRef
llvm_function_reference(LLVMJitContext *context,
						LLVMBuilderRef builder,
						LLVMModuleRef mod,
						FunctionCallInfo fcinfo)
{
	char	   *modname;
	char	   *basename;
	char	   *funcname;

	LLVMValueRef v_fn;

	fmgr_symbol(fcinfo->flinfo->fn_oid, &modname, &basename);

	if (modname != NULL && basename != NULL)
	{
		/* external function in loadable library */
		funcname = psprintf("pgextern.%s.%s", modname, basename);
	}
	else if (basename != NULL)
	{
		/* internal function */
		funcname = psprintf("%s", basename);
	}
	else
	{
		/*
		 * Function we don't know to handle, return pointer. We do so by
		 * creating a global constant containing a pointer to the function.
		 * Makes IR more readable.
		 */
		LLVMValueRef v_fn_addr;

		funcname = psprintf("pgoidextern.%u",
							fcinfo->flinfo->fn_oid);
		v_fn = LLVMGetNamedGlobal(mod, funcname);
		if (v_fn != 0)
			return LLVMBuildLoad(builder, v_fn, "");

		v_fn_addr = l_ptr_const(fcinfo->flinfo->fn_addr, TypePGFunction);

		v_fn = LLVMAddGlobal(mod, TypePGFunction, funcname);
		LLVMSetInitializer(v_fn, v_fn_addr);
		LLVMSetGlobalConstant(v_fn, true);

		return LLVMBuildLoad(builder, v_fn, "");
	}

	/* check if function already has been added */
	v_fn = LLVMGetNamedFunction(mod, funcname);
	if (v_fn != 0)
		return v_fn;

	v_fn = LLVMAddFunction(mod, funcname, LLVMGetElementType(TypePGFunction));

	return v_fn;
}