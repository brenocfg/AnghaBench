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
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
#define  jpiAbs 152 
#define  jpiAdd 151 
#define  jpiAnd 150 
#define  jpiCeiling 149 
#define  jpiDatetime 148 
#define  jpiDiv 147 
#define  jpiDouble 146 
#define  jpiEqual 145 
#define  jpiFloor 144 
#define  jpiGreater 143 
#define  jpiGreaterOrEqual 142 
#define  jpiKeyValue 141 
#define  jpiLess 140 
#define  jpiLessOrEqual 139 
#define  jpiLikeRegex 138 
#define  jpiMinus 137 
#define  jpiMod 136 
#define  jpiMul 135 
#define  jpiNotEqual 134 
#define  jpiOr 133 
#define  jpiPlus 132 
#define  jpiSize 131 
#define  jpiStartsWith 130 
#define  jpiSub 129 
#define  jpiType 128 

const char *
jspOperationName(JsonPathItemType type)
{
	switch (type)
	{
		case jpiAnd:
			return "&&";
		case jpiOr:
			return "||";
		case jpiEqual:
			return "==";
		case jpiNotEqual:
			return "!=";
		case jpiLess:
			return "<";
		case jpiGreater:
			return ">";
		case jpiLessOrEqual:
			return "<=";
		case jpiGreaterOrEqual:
			return ">=";
		case jpiPlus:
		case jpiAdd:
			return "+";
		case jpiMinus:
		case jpiSub:
			return "-";
		case jpiMul:
			return "*";
		case jpiDiv:
			return "/";
		case jpiMod:
			return "%";
		case jpiStartsWith:
			return "starts with";
		case jpiLikeRegex:
			return "like_regex";
		case jpiType:
			return "type";
		case jpiSize:
			return "size";
		case jpiKeyValue:
			return "keyvalue";
		case jpiDouble:
			return "double";
		case jpiAbs:
			return "abs";
		case jpiFloor:
			return "floor";
		case jpiCeiling:
			return "ceiling";
		case jpiDatetime:
			return "datetime";
		default:
			elog(ERROR, "unrecognized jsonpath item type: %d", type);
			return NULL;
	}
}