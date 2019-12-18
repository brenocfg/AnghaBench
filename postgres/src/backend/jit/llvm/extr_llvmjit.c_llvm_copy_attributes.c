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
typedef  int /*<<< orphan*/  LLVMAttributeRef ;

/* Variables and functions */
 int /*<<< orphan*/  LLVMAddAttributeAtIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMAttributeFunctionIndex ; 
 int LLVMGetAttributeCountAtIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLVMGetAttributesAtIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * palloc (int) ; 

void
llvm_copy_attributes(LLVMValueRef v_from, LLVMValueRef v_to)
{
	int			num_attributes;
	int			attno;
	LLVMAttributeRef *attrs;

	num_attributes =
		LLVMGetAttributeCountAtIndex(v_from, LLVMAttributeFunctionIndex);

	attrs = palloc(sizeof(LLVMAttributeRef) * num_attributes);
	LLVMGetAttributesAtIndex(v_from, LLVMAttributeFunctionIndex, attrs);

	for (attno = 0; attno < num_attributes; attno++)
	{
		LLVMAddAttributeAtIndex(v_to, LLVMAttributeFunctionIndex,
								attrs[attno]);
	}
}