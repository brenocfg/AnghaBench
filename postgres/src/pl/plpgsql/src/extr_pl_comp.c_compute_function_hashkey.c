#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* tg_trigger; } ;
typedef  TYPE_4__ TriggerData ;
struct TYPE_14__ {int /*<<< orphan*/  values; } ;
struct TYPE_19__ {int pronargs; int /*<<< orphan*/  proname; TYPE_2__ proargtypes; } ;
struct TYPE_18__ {TYPE_3__* flinfo; int /*<<< orphan*/  fncollation; scalar_t__ context; } ;
struct TYPE_17__ {int /*<<< orphan*/  argtypes; int /*<<< orphan*/  inputCollation; int /*<<< orphan*/  trigOid; scalar_t__ isTrigger; int /*<<< orphan*/  funcOid; } ;
struct TYPE_15__ {int /*<<< orphan*/  fn_expr; int /*<<< orphan*/  fn_oid; } ;
struct TYPE_13__ {int /*<<< orphan*/  tgoid; } ;
typedef  TYPE_5__ PLpgSQL_func_hashkey ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_6__* FunctionCallInfo ;
typedef  TYPE_7__* Form_pg_proc ;

/* Variables and functions */
 scalar_t__ CALLED_AS_TRIGGER (TYPE_6__*) ; 
 int /*<<< orphan*/  MemSet (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plpgsql_resolve_polymorphic_argtypes (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compute_function_hashkey(FunctionCallInfo fcinfo,
						 Form_pg_proc procStruct,
						 PLpgSQL_func_hashkey *hashkey,
						 bool forValidator)
{
	/* Make sure any unused bytes of the struct are zero */
	MemSet(hashkey, 0, sizeof(PLpgSQL_func_hashkey));

	/* get function OID */
	hashkey->funcOid = fcinfo->flinfo->fn_oid;

	/* get call context */
	hashkey->isTrigger = CALLED_AS_TRIGGER(fcinfo);

	/*
	 * if trigger, get its OID.  In validation mode we do not know what
	 * relation or transition table names are intended to be used, so we leave
	 * trigOid zero; the hash entry built in this case will never really be
	 * used.
	 */
	if (hashkey->isTrigger && !forValidator)
	{
		TriggerData *trigdata = (TriggerData *) fcinfo->context;

		hashkey->trigOid = trigdata->tg_trigger->tgoid;
	}

	/* get input collation, if known */
	hashkey->inputCollation = fcinfo->fncollation;

	if (procStruct->pronargs > 0)
	{
		/* get the argument types */
		memcpy(hashkey->argtypes, procStruct->proargtypes.values,
			   procStruct->pronargs * sizeof(Oid));

		/* resolve any polymorphic argument types */
		plpgsql_resolve_polymorphic_argtypes(procStruct->pronargs,
											 hashkey->argtypes,
											 NULL,
											 fcinfo->flinfo->fn_expr,
											 forValidator,
											 NameStr(procStruct->proname));
	}
}