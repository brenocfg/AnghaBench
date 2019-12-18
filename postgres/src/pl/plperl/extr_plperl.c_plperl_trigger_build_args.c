#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_8__ {int /*<<< orphan*/  tg_event; TYPE_5__* tg_relation; TYPE_1__* tg_trigger; int /*<<< orphan*/  tg_newtuple; int /*<<< orphan*/  tg_trigtuple; } ;
typedef  TYPE_2__ TriggerData ;
struct TYPE_10__ {int /*<<< orphan*/  rd_id; int /*<<< orphan*/  rd_att; } ;
struct TYPE_9__ {scalar_t__ context; } ;
struct TYPE_7__ {char* tgname; int tgnargs; char** tgargs; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  HV ;
typedef  TYPE_3__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 char* SPI_getnspname (TYPE_5__*) ; 
 char* SPI_getrelname (TYPE_5__*) ; 
 scalar_t__ TRIGGER_FIRED_AFTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_BEFORE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_BY_DELETE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_BY_INSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_BY_TRUNCATE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_BY_UPDATE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_FOR_ROW (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_FOR_STATEMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRED_INSTEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_extend (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstr2sv (char*) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  hv_ksplit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hv_store_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newAV () ; 
 int /*<<< orphan*/ * newHV () ; 
 int /*<<< orphan*/ * newRV_noinc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newSViv (int) ; 
 int /*<<< orphan*/  oidout ; 
 int /*<<< orphan*/ * plperl_hash_from_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static SV  *
plperl_trigger_build_args(FunctionCallInfo fcinfo)
{
	dTHX;
	TriggerData *tdata;
	TupleDesc	tupdesc;
	int			i;
	char	   *level;
	char	   *event;
	char	   *relid;
	char	   *when;
	HV		   *hv;

	hv = newHV();
	hv_ksplit(hv, 12);			/* pre-grow the hash */

	tdata = (TriggerData *) fcinfo->context;
	tupdesc = tdata->tg_relation->rd_att;

	relid = DatumGetCString(
							DirectFunctionCall1(oidout,
												ObjectIdGetDatum(tdata->tg_relation->rd_id)
												)
		);

	hv_store_string(hv, "name", cstr2sv(tdata->tg_trigger->tgname));
	hv_store_string(hv, "relid", cstr2sv(relid));

	/*
	 * Note: In BEFORE trigger, stored generated columns are not computed yet,
	 * so don't make them accessible in NEW row.
	 */

	if (TRIGGER_FIRED_BY_INSERT(tdata->tg_event))
	{
		event = "INSERT";
		if (TRIGGER_FIRED_FOR_ROW(tdata->tg_event))
			hv_store_string(hv, "new",
							plperl_hash_from_tuple(tdata->tg_trigtuple,
												   tupdesc,
												   !TRIGGER_FIRED_BEFORE(tdata->tg_event)));
	}
	else if (TRIGGER_FIRED_BY_DELETE(tdata->tg_event))
	{
		event = "DELETE";
		if (TRIGGER_FIRED_FOR_ROW(tdata->tg_event))
			hv_store_string(hv, "old",
							plperl_hash_from_tuple(tdata->tg_trigtuple,
												   tupdesc,
												   true));
	}
	else if (TRIGGER_FIRED_BY_UPDATE(tdata->tg_event))
	{
		event = "UPDATE";
		if (TRIGGER_FIRED_FOR_ROW(tdata->tg_event))
		{
			hv_store_string(hv, "old",
							plperl_hash_from_tuple(tdata->tg_trigtuple,
												   tupdesc,
												   true));
			hv_store_string(hv, "new",
							plperl_hash_from_tuple(tdata->tg_newtuple,
												   tupdesc,
												   !TRIGGER_FIRED_BEFORE(tdata->tg_event)));
		}
	}
	else if (TRIGGER_FIRED_BY_TRUNCATE(tdata->tg_event))
		event = "TRUNCATE";
	else
		event = "UNKNOWN";

	hv_store_string(hv, "event", cstr2sv(event));
	hv_store_string(hv, "argc", newSViv(tdata->tg_trigger->tgnargs));

	if (tdata->tg_trigger->tgnargs > 0)
	{
		AV		   *av = newAV();

		av_extend(av, tdata->tg_trigger->tgnargs);
		for (i = 0; i < tdata->tg_trigger->tgnargs; i++)
			av_push(av, cstr2sv(tdata->tg_trigger->tgargs[i]));
		hv_store_string(hv, "args", newRV_noinc((SV *) av));
	}

	hv_store_string(hv, "relname",
					cstr2sv(SPI_getrelname(tdata->tg_relation)));

	hv_store_string(hv, "table_name",
					cstr2sv(SPI_getrelname(tdata->tg_relation)));

	hv_store_string(hv, "table_schema",
					cstr2sv(SPI_getnspname(tdata->tg_relation)));

	if (TRIGGER_FIRED_BEFORE(tdata->tg_event))
		when = "BEFORE";
	else if (TRIGGER_FIRED_AFTER(tdata->tg_event))
		when = "AFTER";
	else if (TRIGGER_FIRED_INSTEAD(tdata->tg_event))
		when = "INSTEAD OF";
	else
		when = "UNKNOWN";
	hv_store_string(hv, "when", cstr2sv(when));

	if (TRIGGER_FIRED_FOR_ROW(tdata->tg_event))
		level = "ROW";
	else if (TRIGGER_FIRED_FOR_STATEMENT(tdata->tg_event))
		level = "STATEMENT";
	else
		level = "UNKNOWN";
	hv_store_string(hv, "level", cstr2sv(level));

	return newRV_noinc((SV *) hv);
}