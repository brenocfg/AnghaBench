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
struct TYPE_9__ {int /*<<< orphan*/  inputcollid; } ;
typedef  TYPE_1__ WindowFunc ;
struct TYPE_16__ {int /*<<< orphan*/  inputcollid; } ;
struct TYPE_15__ {int /*<<< orphan*/  inputcollid; } ;
struct TYPE_14__ {int /*<<< orphan*/  inputcollid; } ;
struct TYPE_13__ {int /*<<< orphan*/  inputcollid; } ;
struct TYPE_12__ {int /*<<< orphan*/  inputcollid; } ;
struct TYPE_11__ {int /*<<< orphan*/  inputcollid; } ;
struct TYPE_10__ {int /*<<< orphan*/  inputcollid; } ;
typedef  TYPE_2__ ScalarArrayOpExpr ;
typedef  TYPE_3__ OpExpr ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ NullIfExpr ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_5__ MinMaxExpr ;
typedef  TYPE_6__ FuncExpr ;
typedef  TYPE_7__ DistinctExpr ;
typedef  TYPE_8__ Aggref ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
#define  T_Aggref 135 
#define  T_DistinctExpr 134 
#define  T_FuncExpr 133 
#define  T_MinMaxExpr 132 
#define  T_NullIfExpr 131 
#define  T_OpExpr 130 
#define  T_ScalarArrayOpExpr 129 
#define  T_WindowFunc 128 
 int nodeTag (int /*<<< orphan*/  const*) ; 

Oid
exprInputCollation(const Node *expr)
{
	Oid			coll;

	if (!expr)
		return InvalidOid;

	switch (nodeTag(expr))
	{
		case T_Aggref:
			coll = ((const Aggref *) expr)->inputcollid;
			break;
		case T_WindowFunc:
			coll = ((const WindowFunc *) expr)->inputcollid;
			break;
		case T_FuncExpr:
			coll = ((const FuncExpr *) expr)->inputcollid;
			break;
		case T_OpExpr:
			coll = ((const OpExpr *) expr)->inputcollid;
			break;
		case T_DistinctExpr:
			coll = ((const DistinctExpr *) expr)->inputcollid;
			break;
		case T_NullIfExpr:
			coll = ((const NullIfExpr *) expr)->inputcollid;
			break;
		case T_ScalarArrayOpExpr:
			coll = ((const ScalarArrayOpExpr *) expr)->inputcollid;
			break;
		case T_MinMaxExpr:
			coll = ((const MinMaxExpr *) expr)->inputcollid;
			break;
		default:
			coll = InvalidOid;
			break;
	}
	return coll;
}