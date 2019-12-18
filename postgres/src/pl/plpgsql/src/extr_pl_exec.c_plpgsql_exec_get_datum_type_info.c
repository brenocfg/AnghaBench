#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_20__ {int dtype; } ;
struct TYPE_19__ {scalar_t__* datums; } ;
struct TYPE_18__ {TYPE_11__* erh; int /*<<< orphan*/  refname; int /*<<< orphan*/  rectypeid; } ;
struct TYPE_14__ {int ftypmod; int /*<<< orphan*/  fcollation; int /*<<< orphan*/  ftypeid; } ;
struct TYPE_17__ {size_t recparentno; TYPE_12__ finfo; int /*<<< orphan*/  rectupledescid; int /*<<< orphan*/  fieldname; } ;
struct TYPE_16__ {TYPE_1__* datatype; } ;
struct TYPE_15__ {int atttypmod; int /*<<< orphan*/  collation; int /*<<< orphan*/  typoid; } ;
struct TYPE_13__ {int /*<<< orphan*/  er_tupdesc_id; int /*<<< orphan*/  er_typeid; } ;
typedef  TYPE_2__ PLpgSQL_var ;
typedef  TYPE_3__ PLpgSQL_recfield ;
typedef  TYPE_4__ PLpgSQL_rec ;
typedef  TYPE_5__ PLpgSQL_execstate ;
typedef  TYPE_6__ PLpgSQL_datum ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
#define  PLPGSQL_DTYPE_PROMISE 131 
#define  PLPGSQL_DTYPE_REC 130 
#define  PLPGSQL_DTYPE_RECFIELD 129 
#define  PLPGSQL_DTYPE_VAR 128 
 int /*<<< orphan*/  RECORDOID ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expanded_record_lookup_field (TYPE_11__*,int /*<<< orphan*/ ,TYPE_12__*) ; 
 int /*<<< orphan*/  instantiate_empty_record_variable (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

void
plpgsql_exec_get_datum_type_info(PLpgSQL_execstate *estate,
								 PLpgSQL_datum *datum,
								 Oid *typeId, int32 *typMod, Oid *collation)
{
	switch (datum->dtype)
	{
		case PLPGSQL_DTYPE_VAR:
		case PLPGSQL_DTYPE_PROMISE:
			{
				PLpgSQL_var *var = (PLpgSQL_var *) datum;

				*typeId = var->datatype->typoid;
				*typMod = var->datatype->atttypmod;
				*collation = var->datatype->collation;
				break;
			}

		case PLPGSQL_DTYPE_REC:
			{
				PLpgSQL_rec *rec = (PLpgSQL_rec *) datum;

				if (rec->erh == NULL || rec->rectypeid != RECORDOID)
				{
					/* Report variable's declared type */
					*typeId = rec->rectypeid;
					*typMod = -1;
				}
				else
				{
					/* Report record's actual type if declared RECORD */
					*typeId = rec->erh->er_typeid;
					/* do NOT return the mutable typmod of a RECORD variable */
					*typMod = -1;
				}
				/* composite types are never collatable */
				*collation = InvalidOid;
				break;
			}

		case PLPGSQL_DTYPE_RECFIELD:
			{
				PLpgSQL_recfield *recfield = (PLpgSQL_recfield *) datum;
				PLpgSQL_rec *rec;

				rec = (PLpgSQL_rec *) (estate->datums[recfield->recparentno]);

				/*
				 * If record variable is NULL, instantiate it if it has a
				 * named composite type, else complain.  (This won't change
				 * the logical state of the record: it's still NULL.)
				 */
				if (rec->erh == NULL)
					instantiate_empty_record_variable(estate, rec);

				/*
				 * Look up the field's properties if we have not already, or
				 * if the tuple descriptor ID changed since last time.
				 */
				if (unlikely(recfield->rectupledescid != rec->erh->er_tupdesc_id))
				{
					if (!expanded_record_lookup_field(rec->erh,
													  recfield->fieldname,
													  &recfield->finfo))
						ereport(ERROR,
								(errcode(ERRCODE_UNDEFINED_COLUMN),
								 errmsg("record \"%s\" has no field \"%s\"",
										rec->refname, recfield->fieldname)));
					recfield->rectupledescid = rec->erh->er_tupdesc_id;
				}

				*typeId = recfield->finfo.ftypeid;
				*typMod = recfield->finfo.ftypmod;
				*collation = recfield->finfo.fcollation;
				break;
			}

		default:
			elog(ERROR, "unrecognized dtype: %d", datum->dtype);
			*typeId = InvalidOid;	/* keep compiler quiet */
			*typMod = -1;
			*collation = InvalidOid;
			break;
	}
}