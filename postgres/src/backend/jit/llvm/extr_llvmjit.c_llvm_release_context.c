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
struct TYPE_5__ {scalar_t__ handles; int /*<<< orphan*/ * module; } ;
struct TYPE_4__ {int /*<<< orphan*/  orc_handle; int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ LLVMJitHandle ;
typedef  TYPE_2__ LLVMJitContext ;
typedef  int /*<<< orphan*/  JitContext ;

/* Variables and functions */
 int /*<<< orphan*/  LLVMDisposeModule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLVMOrcRemoveModule (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 scalar_t__ linitial (scalar_t__) ; 
 scalar_t__ list_delete_first (scalar_t__) ; 
 int /*<<< orphan*/  llvm_enter_fatal_on_oom () ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_exit_inprogress ; 

__attribute__((used)) static void
llvm_release_context(JitContext *context)
{
	LLVMJitContext *llvm_context = (LLVMJitContext *) context;

	llvm_enter_fatal_on_oom();

	/*
	 * When this backend is exiting, don't clean up LLVM. As an error might
	 * have occurred from within LLVM, we do not want to risk reentering. All
	 * resource cleanup is going to happen through process exit.
	 */
	if (!proc_exit_inprogress)
	{
		if (llvm_context->module)
		{
			LLVMDisposeModule(llvm_context->module);
			llvm_context->module = NULL;
		}

		while (llvm_context->handles != NIL)
		{
			LLVMJitHandle *jit_handle;

			jit_handle = (LLVMJitHandle *) linitial(llvm_context->handles);
			llvm_context->handles = list_delete_first(llvm_context->handles);

			LLVMOrcRemoveModule(jit_handle->stack, jit_handle->orc_handle);
			pfree(jit_handle);
		}
	}
}