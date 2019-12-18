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
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  module; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/ * LLVMValueRef ;
typedef  int /*<<< orphan*/  LLVMPassManagerRef ;
typedef  int /*<<< orphan*/  LLVMPassManagerBuilderRef ;
typedef  int /*<<< orphan*/  LLVMModuleRef ;
typedef  TYPE_2__ LLVMJitContext ;

/* Variables and functions */
 int /*<<< orphan*/  LLVMAddAlwaysInlinerPass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMAddFunctionInliningPass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMAddPromoteMemoryToRegisterPass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMCreateFunctionPassManagerForModule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMCreatePassManager () ; 
 int /*<<< orphan*/  LLVMDisposePassManager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMFinalizeFunctionPassManager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LLVMGetFirstFunction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LLVMGetNextFunction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLVMInitializeFunctionPassManager (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMPassManagerBuilderCreate () ; 
 int /*<<< orphan*/  LLVMPassManagerBuilderDispose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMPassManagerBuilderPopulateFunctionPassManager (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMPassManagerBuilderPopulateModulePassManager (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMPassManagerBuilderSetOptLevel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LLVMPassManagerBuilderUseInlinerWithThreshold (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LLVMRunFunctionPassManager (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLVMRunPassManager (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PGJIT_INLINE ; 
 int PGJIT_OPT3 ; 

__attribute__((used)) static void
llvm_optimize_module(LLVMJitContext *context, LLVMModuleRef module)
{
	LLVMPassManagerBuilderRef llvm_pmb;
	LLVMPassManagerRef llvm_mpm;
	LLVMPassManagerRef llvm_fpm;
	LLVMValueRef func;
	int			compile_optlevel;

	if (context->base.flags & PGJIT_OPT3)
		compile_optlevel = 3;
	else
		compile_optlevel = 0;

	/*
	 * Have to create a new pass manager builder every pass through, as the
	 * inliner has some per-builder state. Otherwise one ends up only inlining
	 * a function the first time though.
	 */
	llvm_pmb = LLVMPassManagerBuilderCreate();
	LLVMPassManagerBuilderSetOptLevel(llvm_pmb, compile_optlevel);
	llvm_fpm = LLVMCreateFunctionPassManagerForModule(module);

	if (context->base.flags & PGJIT_OPT3)
	{
		/* TODO: Unscientifically determined threshold */
		LLVMPassManagerBuilderUseInlinerWithThreshold(llvm_pmb, 512);
	}
	else
	{
		/* we rely on mem2reg heavily, so emit even in the O0 case */
		LLVMAddPromoteMemoryToRegisterPass(llvm_fpm);
	}

	LLVMPassManagerBuilderPopulateFunctionPassManager(llvm_pmb, llvm_fpm);

	/*
	 * Do function level optimization. This could be moved to the point where
	 * functions are emitted, to reduce memory usage a bit.
	 */
	LLVMInitializeFunctionPassManager(llvm_fpm);
	for (func = LLVMGetFirstFunction(context->module);
		 func != NULL;
		 func = LLVMGetNextFunction(func))
		LLVMRunFunctionPassManager(llvm_fpm, func);
	LLVMFinalizeFunctionPassManager(llvm_fpm);
	LLVMDisposePassManager(llvm_fpm);

	/*
	 * Perform module level optimization. We do so even in the non-optimized
	 * case, so always-inline functions etc get inlined. It's cheap enough.
	 */
	llvm_mpm = LLVMCreatePassManager();
	LLVMPassManagerBuilderPopulateModulePassManager(llvm_pmb,
													llvm_mpm);
	/* always use always-inliner pass */
	if (!(context->base.flags & PGJIT_OPT3))
		LLVMAddAlwaysInlinerPass(llvm_mpm);
	/* if doing inlining, but no expensive optimization, add inlining pass */
	if (context->base.flags & PGJIT_INLINE
		&& !(context->base.flags & PGJIT_OPT3))
		LLVMAddFunctionInliningPass(llvm_mpm);
	LLVMRunPassManager(llvm_mpm, context->module);
	LLVMDisposePassManager(llvm_mpm);

	LLVMPassManagerBuilderDispose(llvm_pmb);
}