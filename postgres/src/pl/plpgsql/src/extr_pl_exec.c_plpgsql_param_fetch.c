#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_25__ {int dtype; } ;
struct TYPE_24__ {int ndatums; TYPE_9__** datums; } ;
struct TYPE_23__ {int rwparam; int /*<<< orphan*/  paramnos; } ;
struct TYPE_22__ {TYPE_13__* erh; } ;
struct TYPE_21__ {size_t recparentno; int /*<<< orphan*/  rectupledescid; int /*<<< orphan*/  finfo; int /*<<< orphan*/  fieldname; } ;
struct TYPE_20__ {TYPE_1__* datatype; } ;
struct TYPE_19__ {int isnull; void* value; scalar_t__ pflags; int /*<<< orphan*/  ptype; } ;
struct TYPE_18__ {int numParams; scalar_t__ parserSetupArg; scalar_t__ paramFetchArg; } ;
struct TYPE_17__ {int typlen; } ;
struct TYPE_16__ {int /*<<< orphan*/  er_tupdesc_id; } ;
typedef  TYPE_2__* ParamListInfo ;
typedef  TYPE_3__ ParamExternData ;
typedef  TYPE_4__ PLpgSQL_var ;
typedef  TYPE_5__ PLpgSQL_recfield ;
typedef  TYPE_6__ PLpgSQL_rec ;
typedef  TYPE_7__ PLpgSQL_expr ;
typedef  TYPE_8__ PLpgSQL_execstate ;
typedef  TYPE_9__ PLpgSQL_datum ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 void* MakeExpandedObjectReadOnly (void*,int,int) ; 
 scalar_t__ PARAM_FLAG_CONST ; 
#define  PLPGSQL_DTYPE_PROMISE 132 
#define  PLPGSQL_DTYPE_REC 131 
#define  PLPGSQL_DTYPE_RECFIELD 130 
#define  PLPGSQL_DTYPE_ROW 129 
#define  PLPGSQL_DTYPE_VAR 128 
 int /*<<< orphan*/  bms_is_member (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_eval_datum (TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int*) ; 
 int /*<<< orphan*/  expanded_record_lookup_field (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static ParamExternData *
plpgsql_param_fetch(ParamListInfo params,
					int paramid, bool speculative,
					ParamExternData *prm)
{
	int			dno;
	PLpgSQL_execstate *estate;
	PLpgSQL_expr *expr;
	PLpgSQL_datum *datum;
	bool		ok = true;
	int32		prmtypmod;

	/* paramid's are 1-based, but dnos are 0-based */
	dno = paramid - 1;
	Assert(dno >= 0 && dno < params->numParams);

	/* fetch back the hook data */
	estate = (PLpgSQL_execstate *) params->paramFetchArg;
	expr = (PLpgSQL_expr *) params->parserSetupArg;
	Assert(params->numParams == estate->ndatums);

	/* now we can access the target datum */
	datum = estate->datums[dno];

	/*
	 * Since copyParamList() or SerializeParamList() will try to materialize
	 * every single parameter slot, it's important to return a dummy param
	 * when asked for a datum that's not supposed to be used by this SQL
	 * expression.  Otherwise we risk failures in exec_eval_datum(), or
	 * copying a lot more data than necessary.
	 */
	if (!bms_is_member(dno, expr->paramnos))
		ok = false;

	/*
	 * If the access is speculative, we prefer to return no data rather than
	 * to fail in exec_eval_datum().  Check the likely failure cases.
	 */
	else if (speculative)
	{
		switch (datum->dtype)
		{
			case PLPGSQL_DTYPE_VAR:
			case PLPGSQL_DTYPE_PROMISE:
				/* always safe */
				break;

			case PLPGSQL_DTYPE_ROW:
				/* should be safe in all interesting cases */
				break;

			case PLPGSQL_DTYPE_REC:
				/* always safe (might return NULL, that's fine) */
				break;

			case PLPGSQL_DTYPE_RECFIELD:
				{
					PLpgSQL_recfield *recfield = (PLpgSQL_recfield *) datum;
					PLpgSQL_rec *rec;

					rec = (PLpgSQL_rec *) (estate->datums[recfield->recparentno]);

					/*
					 * If record variable is NULL, don't risk anything.
					 */
					if (rec->erh == NULL)
						ok = false;

					/*
					 * Look up the field's properties if we have not already,
					 * or if the tuple descriptor ID changed since last time.
					 */
					else if (unlikely(recfield->rectupledescid != rec->erh->er_tupdesc_id))
					{
						if (expanded_record_lookup_field(rec->erh,
														 recfield->fieldname,
														 &recfield->finfo))
							recfield->rectupledescid = rec->erh->er_tupdesc_id;
						else
							ok = false;
					}
					break;
				}

			default:
				ok = false;
				break;
		}
	}

	/* Return "no such parameter" if not ok */
	if (!ok)
	{
		prm->value = (Datum) 0;
		prm->isnull = true;
		prm->pflags = 0;
		prm->ptype = InvalidOid;
		return prm;
	}

	/* OK, evaluate the value and store into the return struct */
	exec_eval_datum(estate, datum,
					&prm->ptype, &prmtypmod,
					&prm->value, &prm->isnull);
	/* We can always mark params as "const" for executor's purposes */
	prm->pflags = PARAM_FLAG_CONST;

	/*
	 * If it's a read/write expanded datum, convert reference to read-only,
	 * unless it's safe to pass as read-write.
	 */
	if (dno != expr->rwparam)
	{
		if (datum->dtype == PLPGSQL_DTYPE_VAR)
			prm->value = MakeExpandedObjectReadOnly(prm->value,
													prm->isnull,
													((PLpgSQL_var *) datum)->datatype->typlen);
		else if (datum->dtype == PLPGSQL_DTYPE_REC)
			prm->value = MakeExpandedObjectReadOnly(prm->value,
													prm->isnull,
													-1);
	}

	return prm;
}