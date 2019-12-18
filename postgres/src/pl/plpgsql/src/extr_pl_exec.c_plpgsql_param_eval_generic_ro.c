#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_15__ {TYPE_3__* ecxt_param_list_info; } ;
struct TYPE_10__ {int paramid; scalar_t__ paramtype; } ;
struct TYPE_11__ {TYPE_1__ cparam; } ;
struct TYPE_14__ {int /*<<< orphan*/ * resnull; int /*<<< orphan*/ * resvalue; TYPE_2__ d; } ;
struct TYPE_13__ {int ndatums; int /*<<< orphan*/ ** datums; } ;
struct TYPE_12__ {scalar_t__ paramFetchArg; } ;
typedef  TYPE_3__* ParamListInfo ;
typedef  TYPE_4__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  PLpgSQL_datum ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_5__ ExprEvalStep ;
typedef  TYPE_6__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MakeExpandedObjectReadOnly (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_eval_datum (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
plpgsql_param_eval_generic_ro(ExprState *state, ExprEvalStep *op,
							  ExprContext *econtext)
{
	ParamListInfo params;
	PLpgSQL_execstate *estate;
	int			dno = op->d.cparam.paramid - 1;
	PLpgSQL_datum *datum;
	Oid			datumtype;
	int32		datumtypmod;

	/* fetch back the hook data */
	params = econtext->ecxt_param_list_info;
	estate = (PLpgSQL_execstate *) params->paramFetchArg;
	Assert(dno >= 0 && dno < estate->ndatums);

	/* now we can access the target datum */
	datum = estate->datums[dno];

	/* fetch datum's value */
	exec_eval_datum(estate, datum,
					&datumtype, &datumtypmod,
					op->resvalue, op->resnull);

	/* safety check -- needed for, eg, record fields */
	if (unlikely(datumtype != op->d.cparam.paramtype))
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("type of parameter %d (%s) does not match that when preparing the plan (%s)",
						op->d.cparam.paramid,
						format_type_be(datumtype),
						format_type_be(op->d.cparam.paramtype))));

	/* force the value to read-only */
	*op->resvalue = MakeExpandedObjectReadOnly(*op->resvalue,
											   *op->resnull,
											   -1);
}