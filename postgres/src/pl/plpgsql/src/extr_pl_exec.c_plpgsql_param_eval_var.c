#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_4__* ecxt_param_list_info; } ;
struct TYPE_12__ {int paramid; scalar_t__ paramtype; } ;
struct TYPE_13__ {TYPE_2__ cparam; } ;
struct TYPE_17__ {TYPE_3__ d; int /*<<< orphan*/ * resnull; int /*<<< orphan*/ * resvalue; } ;
struct TYPE_16__ {int ndatums; scalar_t__* datums; } ;
struct TYPE_15__ {scalar_t__ dtype; TYPE_1__* datatype; int /*<<< orphan*/  isnull; int /*<<< orphan*/  value; } ;
struct TYPE_14__ {scalar_t__ paramFetchArg; } ;
struct TYPE_11__ {scalar_t__ typoid; } ;
typedef  TYPE_4__* ParamListInfo ;
typedef  TYPE_5__ PLpgSQL_var ;
typedef  TYPE_6__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_7__ ExprEvalStep ;
typedef  TYPE_8__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ PLPGSQL_DTYPE_VAR ; 

__attribute__((used)) static void
plpgsql_param_eval_var(ExprState *state, ExprEvalStep *op,
					   ExprContext *econtext)
{
	ParamListInfo params;
	PLpgSQL_execstate *estate;
	int			dno = op->d.cparam.paramid - 1;
	PLpgSQL_var *var;

	/* fetch back the hook data */
	params = econtext->ecxt_param_list_info;
	estate = (PLpgSQL_execstate *) params->paramFetchArg;
	Assert(dno >= 0 && dno < estate->ndatums);

	/* now we can access the target datum */
	var = (PLpgSQL_var *) estate->datums[dno];
	Assert(var->dtype == PLPGSQL_DTYPE_VAR);

	/* inlined version of exec_eval_datum() */
	*op->resvalue = var->value;
	*op->resnull = var->isnull;

	/* safety check -- an assertion should be sufficient */
	Assert(var->datatype->typoid == op->d.cparam.paramtype);
}