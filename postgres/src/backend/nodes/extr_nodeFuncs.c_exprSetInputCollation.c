#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* inputcollid; } ;
typedef  TYPE_1__ WindowFunc ;
struct TYPE_16__ {void* inputcollid; } ;
struct TYPE_15__ {void* inputcollid; } ;
struct TYPE_14__ {void* inputcollid; } ;
struct TYPE_13__ {void* inputcollid; } ;
struct TYPE_12__ {void* inputcollid; } ;
struct TYPE_11__ {void* inputcollid; } ;
struct TYPE_10__ {void* inputcollid; } ;
typedef  TYPE_2__ ScalarArrayOpExpr ;
typedef  TYPE_3__ OpExpr ;
typedef  void* Oid ;
typedef  TYPE_4__ NullIfExpr ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_5__ MinMaxExpr ;
typedef  TYPE_6__ FuncExpr ;
typedef  TYPE_7__ DistinctExpr ;
typedef  TYPE_8__ Aggref ;

/* Variables and functions */
#define  T_Aggref 135 
#define  T_DistinctExpr 134 
#define  T_FuncExpr 133 
#define  T_MinMaxExpr 132 
#define  T_NullIfExpr 131 
#define  T_OpExpr 130 
#define  T_ScalarArrayOpExpr 129 
#define  T_WindowFunc 128 
 int nodeTag (int /*<<< orphan*/ *) ; 

void
exprSetInputCollation(Node *expr, Oid inputcollation)
{
	switch (nodeTag(expr))
	{
		case T_Aggref:
			((Aggref *) expr)->inputcollid = inputcollation;
			break;
		case T_WindowFunc:
			((WindowFunc *) expr)->inputcollid = inputcollation;
			break;
		case T_FuncExpr:
			((FuncExpr *) expr)->inputcollid = inputcollation;
			break;
		case T_OpExpr:
			((OpExpr *) expr)->inputcollid = inputcollation;
			break;
		case T_DistinctExpr:
			((DistinctExpr *) expr)->inputcollid = inputcollation;
			break;
		case T_NullIfExpr:
			((NullIfExpr *) expr)->inputcollid = inputcollation;
			break;
		case T_ScalarArrayOpExpr:
			((ScalarArrayOpExpr *) expr)->inputcollid = inputcollation;
			break;
		case T_MinMaxExpr:
			((MinMaxExpr *) expr)->inputcollid = inputcollation;
			break;
		default:
			break;
	}
}