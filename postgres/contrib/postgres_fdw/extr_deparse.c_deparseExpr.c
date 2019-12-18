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
typedef  int /*<<< orphan*/  deparse_expr_cxt ;
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  SubscriptingRef ;
typedef  int /*<<< orphan*/  ScalarArrayOpExpr ;
typedef  int /*<<< orphan*/  RelabelType ;
typedef  int /*<<< orphan*/  Param ;
typedef  int /*<<< orphan*/  OpExpr ;
typedef  int /*<<< orphan*/  NullTest ;
typedef  int /*<<< orphan*/  FuncExpr ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  DistinctExpr ;
typedef  int /*<<< orphan*/  Const ;
typedef  int /*<<< orphan*/  BoolExpr ;
typedef  int /*<<< orphan*/  ArrayExpr ;
typedef  int /*<<< orphan*/  Aggref ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  T_Aggref 140 
#define  T_ArrayExpr 139 
#define  T_BoolExpr 138 
#define  T_Const 137 
#define  T_DistinctExpr 136 
#define  T_FuncExpr 135 
#define  T_NullTest 134 
#define  T_OpExpr 133 
#define  T_Param 132 
#define  T_RelabelType 131 
#define  T_ScalarArrayOpExpr 130 
#define  T_SubscriptingRef 129 
#define  T_Var 128 
 int /*<<< orphan*/  deparseAggref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseArrayExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseBoolExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseConst (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deparseDistinctExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseFuncExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseNullTest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseOpExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseParam (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseRelabelType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseScalarArrayOpExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseSubscriptingRef (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deparseVar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
deparseExpr(Expr *node, deparse_expr_cxt *context)
{
	if (node == NULL)
		return;

	switch (nodeTag(node))
	{
		case T_Var:
			deparseVar((Var *) node, context);
			break;
		case T_Const:
			deparseConst((Const *) node, context, 0);
			break;
		case T_Param:
			deparseParam((Param *) node, context);
			break;
		case T_SubscriptingRef:
			deparseSubscriptingRef((SubscriptingRef *) node, context);
			break;
		case T_FuncExpr:
			deparseFuncExpr((FuncExpr *) node, context);
			break;
		case T_OpExpr:
			deparseOpExpr((OpExpr *) node, context);
			break;
		case T_DistinctExpr:
			deparseDistinctExpr((DistinctExpr *) node, context);
			break;
		case T_ScalarArrayOpExpr:
			deparseScalarArrayOpExpr((ScalarArrayOpExpr *) node, context);
			break;
		case T_RelabelType:
			deparseRelabelType((RelabelType *) node, context);
			break;
		case T_BoolExpr:
			deparseBoolExpr((BoolExpr *) node, context);
			break;
		case T_NullTest:
			deparseNullTest((NullTest *) node, context);
			break;
		case T_ArrayExpr:
			deparseArrayExpr((ArrayExpr *) node, context);
			break;
		case T_Aggref:
			deparseAggref((Aggref *) node, context);
			break;
		default:
			elog(ERROR, "unsupported expression type for deparse: %d",
				 (int) nodeTag(node));
			break;
	}
}