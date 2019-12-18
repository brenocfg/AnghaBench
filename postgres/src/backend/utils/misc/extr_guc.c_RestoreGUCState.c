#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  varsourceline ;
typedef  int /*<<< orphan*/  varsource ;
typedef  int /*<<< orphan*/  varscontext ;
typedef  int /*<<< orphan*/  len ;
struct TYPE_3__ {char** arg; struct TYPE_3__* previous; int /*<<< orphan*/  callback; } ;
typedef  int Size ;
typedef  int GucSource ;
typedef  int GucContext ;
typedef  TYPE_1__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GUC_ACTION_SET ; 
 int /*<<< orphan*/  InitializeOneGUCOption (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_skip_gucvar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 TYPE_1__* error_context_stack ; 
 int /*<<< orphan*/  guc_restore_error_context_callback ; 
 int /*<<< orphan*/ * guc_variables ; 
 int /*<<< orphan*/  memcpy (int*,void*,int) ; 
 int num_guc_variables ; 
 char* read_gucstate (char**,char*) ; 
 int /*<<< orphan*/  read_gucstate_binary (char**,char*,int*,int) ; 
 int set_config_option (char*,char*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_config_sourcefile (char*,char*,int) ; 

void
RestoreGUCState(void *gucstate)
{
	char	   *varname,
			   *varvalue,
			   *varsourcefile;
	int			varsourceline;
	GucSource	varsource;
	GucContext	varscontext;
	char	   *srcptr = (char *) gucstate;
	char	   *srcend;
	Size		len;
	int			i;
	ErrorContextCallback error_context_callback;

	/* See comment at can_skip_gucvar(). */
	for (i = 0; i < num_guc_variables; i++)
		if (!can_skip_gucvar(guc_variables[i]))
			InitializeOneGUCOption(guc_variables[i]);

	/* First item is the length of the subsequent data */
	memcpy(&len, gucstate, sizeof(len));

	srcptr += sizeof(len);
	srcend = srcptr + len;

	/* If the GUC value check fails, we want errors to show useful context. */
	error_context_callback.callback = guc_restore_error_context_callback;
	error_context_callback.previous = error_context_stack;
	error_context_callback.arg = NULL;
	error_context_stack = &error_context_callback;

	while (srcptr < srcend)
	{
		int			result;
		char	   *error_context_name_and_value[2];

		varname = read_gucstate(&srcptr, srcend);
		varvalue = read_gucstate(&srcptr, srcend);
		varsourcefile = read_gucstate(&srcptr, srcend);
		if (varsourcefile[0])
			read_gucstate_binary(&srcptr, srcend,
								 &varsourceline, sizeof(varsourceline));
		else
			varsourceline = 0;
		read_gucstate_binary(&srcptr, srcend,
							 &varsource, sizeof(varsource));
		read_gucstate_binary(&srcptr, srcend,
							 &varscontext, sizeof(varscontext));

		error_context_name_and_value[0] = varname;
		error_context_name_and_value[1] = varvalue;
		error_context_callback.arg = &error_context_name_and_value[0];
		result = set_config_option(varname, varvalue, varscontext, varsource,
								   GUC_ACTION_SET, true, ERROR, true);
		if (result <= 0)
			ereport(ERROR,
					(errcode(ERRCODE_INTERNAL_ERROR),
					 errmsg("parameter \"%s\" could not be set", varname)));
		if (varsourcefile[0])
			set_config_sourcefile(varname, varsourcefile, varsourceline);
		error_context_callback.arg = NULL;
	}

	error_context_stack = error_context_callback.previous;
}