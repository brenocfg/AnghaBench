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
typedef  int /*<<< orphan*/  LLVMValueRef ;
typedef  int /*<<< orphan*/ * LLVMTypeRef ;
typedef  int /*<<< orphan*/  LLVMModuleRef ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * LLVMGetElementType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLVMGetNamedGlobal (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * LLVMTypeOf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static LLVMTypeRef
load_type(LLVMModuleRef mod, const char *name)
{
	LLVMValueRef value;
	LLVMTypeRef typ;

	/* this'll return a *pointer* to the global */
	value = LLVMGetNamedGlobal(mod, name);
	if (!value)
		elog(ERROR, "type %s is unknown", name);

	/* therefore look at the contained type and return that */
	typ = LLVMTypeOf(value);
	Assert(typ != NULL);
	typ = LLVMGetElementType(typ);
	Assert(typ != NULL);
	return typ;
}