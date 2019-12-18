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
typedef  int /*<<< orphan*/  LLVMTypeRef ;
typedef  int /*<<< orphan*/  LLVMModuleRef ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ LLVMAddFunction (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMCCallConv ; 
 int /*<<< orphan*/  LLVMFunctionType (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LLVMGetIntrinsicID (scalar_t__) ; 
 scalar_t__ LLVMGetNamedFunction (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  LLVMInt64Type () ; 
 int /*<<< orphan*/  LLVMInt8Type () ; 
 int /*<<< orphan*/  LLVMSetFunctionCallConv (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMVoidType () ; 
 int /*<<< orphan*/  l_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lengthof (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LLVMValueRef
create_LifetimeEnd(LLVMModuleRef mod)
{
	LLVMTypeRef sig;
	LLVMValueRef fn;
	LLVMTypeRef param_types[2];

	/* LLVM 5+ has a variadic pointer argument */
#if LLVM_VERSION_MAJOR < 5
	const char *nm = "llvm.lifetime.end";
#else
	const char *nm = "llvm.lifetime.end.p0i8";
#endif

	fn = LLVMGetNamedFunction(mod, nm);
	if (fn)
		return fn;

	param_types[0] = LLVMInt64Type();
	param_types[1] = l_ptr(LLVMInt8Type());

	sig = LLVMFunctionType(LLVMVoidType(),
						   param_types, lengthof(param_types),
						   false);
	fn = LLVMAddFunction(mod, nm, sig);

	LLVMSetFunctionCallConv(fn, LLVMCCallConv);

	Assert(LLVMGetIntrinsicID(fn));

	return fn;
}