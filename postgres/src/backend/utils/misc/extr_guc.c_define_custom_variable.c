#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sourceline; scalar_t__ sourcefile; int /*<<< orphan*/  source; int /*<<< orphan*/  scontext; int /*<<< orphan*/  stack; int /*<<< orphan*/  reset_source; int /*<<< orphan*/  reset_scontext; } ;
struct config_string {scalar_t__ reset_val; scalar_t__* variable; TYPE_1__ gen; } ;
struct config_generic {char* name; int flags; scalar_t__ vartype; int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GUC_ACTION_SET ; 
 int GUC_CUSTOM_PLACEHOLDER ; 
 int /*<<< orphan*/  InitializeOneGUCOption (struct config_generic*) ; 
 scalar_t__ PGC_STRING ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  add_guc_variable (struct config_generic*,int /*<<< orphan*/ ) ; 
 scalar_t__ bsearch (void*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  free (struct config_string*) ; 
 int /*<<< orphan*/  guc_var_compare ; 
 scalar_t__ guc_variables ; 
 int /*<<< orphan*/  num_guc_variables ; 
 int /*<<< orphan*/  reapply_stacked_values (struct config_generic*,struct config_string*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_config_option (char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_config_sourcefile (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_string_field (struct config_string*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
define_custom_variable(struct config_generic *variable)
{
	const char *name = variable->name;
	const char **nameAddr = &name;
	struct config_string *pHolder;
	struct config_generic **res;

	/*
	 * See if there's a placeholder by the same name.
	 */
	res = (struct config_generic **) bsearch((void *) &nameAddr,
											 (void *) guc_variables,
											 num_guc_variables,
											 sizeof(struct config_generic *),
											 guc_var_compare);
	if (res == NULL)
	{
		/*
		 * No placeholder to replace, so we can just add it ... but first,
		 * make sure it's initialized to its default value.
		 */
		InitializeOneGUCOption(variable);
		add_guc_variable(variable, ERROR);
		return;
	}

	/*
	 * This better be a placeholder
	 */
	if (((*res)->flags & GUC_CUSTOM_PLACEHOLDER) == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("attempt to redefine parameter \"%s\"", name)));

	Assert((*res)->vartype == PGC_STRING);
	pHolder = (struct config_string *) (*res);

	/*
	 * First, set the variable to its default value.  We must do this even
	 * though we intend to immediately apply a new value, since it's possible
	 * that the new value is invalid.
	 */
	InitializeOneGUCOption(variable);

	/*
	 * Replace the placeholder. We aren't changing the name, so no re-sorting
	 * is necessary
	 */
	*res = variable;

	/*
	 * Assign the string value(s) stored in the placeholder to the real
	 * variable.  Essentially, we need to duplicate all the active and stacked
	 * values, but with appropriate validation and datatype adjustment.
	 *
	 * If an assignment fails, we report a WARNING and keep going.  We don't
	 * want to throw ERROR for bad values, because it'd bollix the add-on
	 * module that's presumably halfway through getting loaded.  In such cases
	 * the default or previous state will become active instead.
	 */

	/* First, apply the reset value if any */
	if (pHolder->reset_val)
		(void) set_config_option(name, pHolder->reset_val,
								 pHolder->gen.reset_scontext,
								 pHolder->gen.reset_source,
								 GUC_ACTION_SET, true, WARNING, false);
	/* That should not have resulted in stacking anything */
	Assert(variable->stack == NULL);

	/* Now, apply current and stacked values, in the order they were stacked */
	reapply_stacked_values(variable, pHolder, pHolder->gen.stack,
						   *(pHolder->variable),
						   pHolder->gen.scontext, pHolder->gen.source);

	/* Also copy over any saved source-location information */
	if (pHolder->gen.sourcefile)
		set_config_sourcefile(name, pHolder->gen.sourcefile,
							  pHolder->gen.sourceline);

	/*
	 * Free up as much as we conveniently can of the placeholder structure.
	 * (This neglects any stack items, so it's possible for some memory to be
	 * leaked.  Since this can only happen once per session per variable, it
	 * doesn't seem worth spending much code on.)
	 */
	set_string_field(pHolder, pHolder->variable, NULL);
	set_string_field(pHolder, &pHolder->reset_val, NULL);

	free(pHolder);
}