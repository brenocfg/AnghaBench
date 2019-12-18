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
struct config_generic {int flags; char* name; char* short_desc; } ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  TupOutputState ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  DEFAULT_ROLE_READ_ALL_SETTINGS ; 
 char* DatumGetPointer (int /*<<< orphan*/ ) ; 
 int GUC_NO_SHOW_ALL ; 
 int GUC_SUPERUSER_ONLY ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 int /*<<< orphan*/  TupleDescInitBuiltinEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* _ShowOption (struct config_generic*,int) ; 
 int /*<<< orphan*/ * begin_tup_output_tupdesc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/  do_tup_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  end_tup_output (int /*<<< orphan*/ *) ; 
 struct config_generic** guc_variables ; 
 int /*<<< orphan*/  is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_guc_variables ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static void
ShowAllGUCConfig(DestReceiver *dest)
{
	int			i;
	TupOutputState *tstate;
	TupleDesc	tupdesc;
	Datum		values[3];
	bool		isnull[3] = {false, false, false};

	/* need a tuple descriptor representing three TEXT columns */
	tupdesc = CreateTemplateTupleDesc(3);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 1, "name",
							  TEXTOID, -1, 0);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 2, "setting",
							  TEXTOID, -1, 0);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 3, "description",
							  TEXTOID, -1, 0);

	/* prepare for projection of tuples */
	tstate = begin_tup_output_tupdesc(dest, tupdesc, &TTSOpsVirtual);

	for (i = 0; i < num_guc_variables; i++)
	{
		struct config_generic *conf = guc_variables[i];
		char	   *setting;

		if ((conf->flags & GUC_NO_SHOW_ALL) ||
			((conf->flags & GUC_SUPERUSER_ONLY) &&
			 !is_member_of_role(GetUserId(), DEFAULT_ROLE_READ_ALL_SETTINGS)))
			continue;

		/* assign to the values array */
		values[0] = PointerGetDatum(cstring_to_text(conf->name));

		setting = _ShowOption(conf, true);
		if (setting)
		{
			values[1] = PointerGetDatum(cstring_to_text(setting));
			isnull[1] = false;
		}
		else
		{
			values[1] = PointerGetDatum(NULL);
			isnull[1] = true;
		}

		values[2] = PointerGetDatum(cstring_to_text(conf->short_desc));

		/* send it to dest */
		do_tup_output(tstate, values, isnull);

		/* clean up */
		pfree(DatumGetPointer(values[0]));
		if (setting)
		{
			pfree(setting);
			pfree(DatumGetPointer(values[1]));
		}
		pfree(DatumGetPointer(values[2]));
	}

	end_tup_output(tstate);
}