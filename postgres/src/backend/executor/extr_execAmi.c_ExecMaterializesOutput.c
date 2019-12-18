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
typedef  int NodeTag ;

/* Variables and functions */
#define  T_CteScan 134 
#define  T_FunctionScan 133 
#define  T_Material 132 
#define  T_NamedTuplestoreScan 131 
#define  T_Sort 130 
#define  T_TableFuncScan 129 
#define  T_WorkTableScan 128 

bool
ExecMaterializesOutput(NodeTag plantype)
{
	switch (plantype)
	{
		case T_Material:
		case T_FunctionScan:
		case T_TableFuncScan:
		case T_CteScan:
		case T_NamedTuplestoreScan:
		case T_WorkTableScan:
		case T_Sort:
			return true;

		default:
			break;
	}

	return false;
}