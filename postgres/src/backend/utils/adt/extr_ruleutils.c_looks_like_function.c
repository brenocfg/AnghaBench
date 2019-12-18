#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  funcformat; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ FuncExpr ;

/* Variables and functions */
 int /*<<< orphan*/  COERCE_EXPLICIT_CALL ; 
#define  T_CoalesceExpr 133 
#define  T_FuncExpr 132 
#define  T_MinMaxExpr 131 
#define  T_NullIfExpr 130 
#define  T_SQLValueFunction 129 
#define  T_XmlExpr 128 
 int nodeTag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
looks_like_function(Node *node)
{
	if (node == NULL)
		return false;			/* probably shouldn't happen */
	switch (nodeTag(node))
	{
		case T_FuncExpr:
			/* OK, unless it's going to deparse as a cast */
			return (((FuncExpr *) node)->funcformat == COERCE_EXPLICIT_CALL);
		case T_NullIfExpr:
		case T_CoalesceExpr:
		case T_MinMaxExpr:
		case T_SQLValueFunction:
		case T_XmlExpr:
			/* these are all accepted by func_expr_common_subexpr */
			return true;
		default:
			break;
	}
	return false;
}