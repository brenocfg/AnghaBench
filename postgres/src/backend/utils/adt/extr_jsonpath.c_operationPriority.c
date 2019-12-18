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
typedef  int JsonPathItemType ;

/* Variables and functions */
#define  jpiAdd 143 
#define  jpiAnd 142 
#define  jpiDiv 141 
#define  jpiEqual 140 
#define  jpiGreater 139 
#define  jpiGreaterOrEqual 138 
#define  jpiLess 137 
#define  jpiLessOrEqual 136 
#define  jpiMinus 135 
#define  jpiMod 134 
#define  jpiMul 133 
#define  jpiNotEqual 132 
#define  jpiOr 131 
#define  jpiPlus 130 
#define  jpiStartsWith 129 
#define  jpiSub 128 

__attribute__((used)) static int
operationPriority(JsonPathItemType op)
{
	switch (op)
	{
		case jpiOr:
			return 0;
		case jpiAnd:
			return 1;
		case jpiEqual:
		case jpiNotEqual:
		case jpiLess:
		case jpiGreater:
		case jpiLessOrEqual:
		case jpiGreaterOrEqual:
		case jpiStartsWith:
			return 2;
		case jpiAdd:
		case jpiSub:
			return 3;
		case jpiMul:
		case jpiDiv:
		case jpiMod:
			return 4;
		case jpiPlus:
		case jpiMinus:
			return 5;
		default:
			return 6;
	}
}