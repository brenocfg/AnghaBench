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
typedef  int /*<<< orphan*/  LLVMModuleRef ;

/* Variables and functions */
 scalar_t__ LLVMAddFunction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMGetElementType (int /*<<< orphan*/ ) ; 
 scalar_t__ LLVMGetNamedFunction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMGetValueName (scalar_t__) ; 
 int /*<<< orphan*/  LLVMTypeOf (scalar_t__) ; 
 int /*<<< orphan*/  llvm_copy_attributes (scalar_t__,scalar_t__) ; 

LLVMValueRef
llvm_get_decl(LLVMModuleRef mod, LLVMValueRef v_src)
{
	LLVMValueRef v_fn;

	/* don't repeatedly add function */
	v_fn = LLVMGetNamedFunction(mod, LLVMGetValueName(v_src));
	if (v_fn)
		return v_fn;

	v_fn = LLVMAddFunction(mod,
						   LLVMGetValueName(v_src),
						   LLVMGetElementType(LLVMTypeOf(v_src)));
	llvm_copy_attributes(v_src, v_fn);

	return v_fn;
}