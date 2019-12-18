#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct config_generic {int vartype; void* extra; int flags; TYPE_3__* stack; int /*<<< orphan*/  scontext; int /*<<< orphan*/  source; } ;
struct config_string {char** variable; struct config_generic gen; int /*<<< orphan*/  (* assign_hook ) (char*,void*) ;} ;
struct config_real {double* variable; struct config_generic gen; int /*<<< orphan*/  (* assign_hook ) (double,void*) ;} ;
struct config_int {int* variable; struct config_generic gen; int /*<<< orphan*/  (* assign_hook ) (int,void*) ;} ;
struct config_enum {int* variable; struct config_generic gen; int /*<<< orphan*/  (* assign_hook ) (int,void*) ;} ;
struct config_bool {int* variable; struct config_generic gen; int /*<<< orphan*/  (* assign_hook ) (int,void*) ;} ;
struct TYPE_6__ {int boolval; int intval; double realval; char* stringval; int enumval; } ;
struct TYPE_7__ {void* extra; TYPE_1__ val; } ;
typedef  TYPE_2__ config_var_value ;
struct TYPE_8__ {int nest_level; int state; TYPE_2__ masked; TYPE_2__ prior; int /*<<< orphan*/  scontext; int /*<<< orphan*/  source; int /*<<< orphan*/  masked_scontext; struct TYPE_8__* prev; } ;
typedef  TYPE_3__ GucStack ;
typedef  int /*<<< orphan*/  GucSource ;
typedef  int /*<<< orphan*/  GucContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int GUCNestLevel ; 
#define  GUC_LOCAL 136 
 int GUC_REPORT ; 
#define  GUC_SAVE 135 
#define  GUC_SET 134 
#define  GUC_SET_LOCAL 133 
#define  PGC_BOOL 132 
#define  PGC_ENUM 131 
#define  PGC_INT 130 
#define  PGC_REAL 129 
#define  PGC_STRING 128 
 int /*<<< orphan*/  PGC_S_SESSION ; 
 int /*<<< orphan*/  ReportGUCOption (struct config_generic*) ; 
 int /*<<< orphan*/  discard_stack_value (struct config_generic*,TYPE_2__*) ; 
 int guc_dirty ; 
 struct config_generic** guc_variables ; 
 int num_guc_variables ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 int /*<<< orphan*/  set_extra_field (struct config_generic*,void**,void*) ; 
 int /*<<< orphan*/  set_string_field (struct config_string*,char**,char*) ; 
 int /*<<< orphan*/  stub1 (int,void*) ; 
 int /*<<< orphan*/  stub2 (int,void*) ; 
 int /*<<< orphan*/  stub3 (double,void*) ; 
 int /*<<< orphan*/  stub4 (char*,void*) ; 
 int /*<<< orphan*/  stub5 (int,void*) ; 

void
AtEOXact_GUC(bool isCommit, int nestLevel)
{
	bool		still_dirty;
	int			i;

	/*
	 * Note: it's possible to get here with GUCNestLevel == nestLevel-1 during
	 * abort, if there is a failure during transaction start before
	 * AtStart_GUC is called.
	 */
	Assert(nestLevel > 0 &&
		   (nestLevel <= GUCNestLevel ||
			(nestLevel == GUCNestLevel + 1 && !isCommit)));

	/* Quick exit if nothing's changed in this transaction */
	if (!guc_dirty)
	{
		GUCNestLevel = nestLevel - 1;
		return;
	}

	still_dirty = false;
	for (i = 0; i < num_guc_variables; i++)
	{
		struct config_generic *gconf = guc_variables[i];
		GucStack   *stack;

		/*
		 * Process and pop each stack entry within the nest level. To simplify
		 * fmgr_security_definer() and other places that use GUC_ACTION_SAVE,
		 * we allow failure exit from code that uses a local nest level to be
		 * recovered at the surrounding transaction or subtransaction abort;
		 * so there could be more than one stack entry to pop.
		 */
		while ((stack = gconf->stack) != NULL &&
			   stack->nest_level >= nestLevel)
		{
			GucStack   *prev = stack->prev;
			bool		restorePrior = false;
			bool		restoreMasked = false;
			bool		changed;

			/*
			 * In this next bit, if we don't set either restorePrior or
			 * restoreMasked, we must "discard" any unwanted fields of the
			 * stack entries to avoid leaking memory.  If we do set one of
			 * those flags, unused fields will be cleaned up after restoring.
			 */
			if (!isCommit)		/* if abort, always restore prior value */
				restorePrior = true;
			else if (stack->state == GUC_SAVE)
				restorePrior = true;
			else if (stack->nest_level == 1)
			{
				/* transaction commit */
				if (stack->state == GUC_SET_LOCAL)
					restoreMasked = true;
				else if (stack->state == GUC_SET)
				{
					/* we keep the current active value */
					discard_stack_value(gconf, &stack->prior);
				}
				else			/* must be GUC_LOCAL */
					restorePrior = true;
			}
			else if (prev == NULL ||
					 prev->nest_level < stack->nest_level - 1)
			{
				/* decrement entry's level and do not pop it */
				stack->nest_level--;
				continue;
			}
			else
			{
				/*
				 * We have to merge this stack entry into prev. See README for
				 * discussion of this bit.
				 */
				switch (stack->state)
				{
					case GUC_SAVE:
						Assert(false);	/* can't get here */
						break;

					case GUC_SET:
						/* next level always becomes SET */
						discard_stack_value(gconf, &stack->prior);
						if (prev->state == GUC_SET_LOCAL)
							discard_stack_value(gconf, &prev->masked);
						prev->state = GUC_SET;
						break;

					case GUC_LOCAL:
						if (prev->state == GUC_SET)
						{
							/* LOCAL migrates down */
							prev->masked_scontext = stack->scontext;
							prev->masked = stack->prior;
							prev->state = GUC_SET_LOCAL;
						}
						else
						{
							/* else just forget this stack level */
							discard_stack_value(gconf, &stack->prior);
						}
						break;

					case GUC_SET_LOCAL:
						/* prior state at this level no longer wanted */
						discard_stack_value(gconf, &stack->prior);
						/* copy down the masked state */
						prev->masked_scontext = stack->masked_scontext;
						if (prev->state == GUC_SET_LOCAL)
							discard_stack_value(gconf, &prev->masked);
						prev->masked = stack->masked;
						prev->state = GUC_SET_LOCAL;
						break;
				}
			}

			changed = false;

			if (restorePrior || restoreMasked)
			{
				/* Perform appropriate restoration of the stacked value */
				config_var_value newvalue;
				GucSource	newsource;
				GucContext	newscontext;

				if (restoreMasked)
				{
					newvalue = stack->masked;
					newsource = PGC_S_SESSION;
					newscontext = stack->masked_scontext;
				}
				else
				{
					newvalue = stack->prior;
					newsource = stack->source;
					newscontext = stack->scontext;
				}

				switch (gconf->vartype)
				{
					case PGC_BOOL:
						{
							struct config_bool *conf = (struct config_bool *) gconf;
							bool		newval = newvalue.val.boolval;
							void	   *newextra = newvalue.extra;

							if (*conf->variable != newval ||
								conf->gen.extra != newextra)
							{
								if (conf->assign_hook)
									conf->assign_hook(newval, newextra);
								*conf->variable = newval;
								set_extra_field(&conf->gen, &conf->gen.extra,
												newextra);
								changed = true;
							}
							break;
						}
					case PGC_INT:
						{
							struct config_int *conf = (struct config_int *) gconf;
							int			newval = newvalue.val.intval;
							void	   *newextra = newvalue.extra;

							if (*conf->variable != newval ||
								conf->gen.extra != newextra)
							{
								if (conf->assign_hook)
									conf->assign_hook(newval, newextra);
								*conf->variable = newval;
								set_extra_field(&conf->gen, &conf->gen.extra,
												newextra);
								changed = true;
							}
							break;
						}
					case PGC_REAL:
						{
							struct config_real *conf = (struct config_real *) gconf;
							double		newval = newvalue.val.realval;
							void	   *newextra = newvalue.extra;

							if (*conf->variable != newval ||
								conf->gen.extra != newextra)
							{
								if (conf->assign_hook)
									conf->assign_hook(newval, newextra);
								*conf->variable = newval;
								set_extra_field(&conf->gen, &conf->gen.extra,
												newextra);
								changed = true;
							}
							break;
						}
					case PGC_STRING:
						{
							struct config_string *conf = (struct config_string *) gconf;
							char	   *newval = newvalue.val.stringval;
							void	   *newextra = newvalue.extra;

							if (*conf->variable != newval ||
								conf->gen.extra != newextra)
							{
								if (conf->assign_hook)
									conf->assign_hook(newval, newextra);
								set_string_field(conf, conf->variable, newval);
								set_extra_field(&conf->gen, &conf->gen.extra,
												newextra);
								changed = true;
							}

							/*
							 * Release stacked values if not used anymore. We
							 * could use discard_stack_value() here, but since
							 * we have type-specific code anyway, might as
							 * well inline it.
							 */
							set_string_field(conf, &stack->prior.val.stringval, NULL);
							set_string_field(conf, &stack->masked.val.stringval, NULL);
							break;
						}
					case PGC_ENUM:
						{
							struct config_enum *conf = (struct config_enum *) gconf;
							int			newval = newvalue.val.enumval;
							void	   *newextra = newvalue.extra;

							if (*conf->variable != newval ||
								conf->gen.extra != newextra)
							{
								if (conf->assign_hook)
									conf->assign_hook(newval, newextra);
								*conf->variable = newval;
								set_extra_field(&conf->gen, &conf->gen.extra,
												newextra);
								changed = true;
							}
							break;
						}
				}

				/*
				 * Release stacked extra values if not used anymore.
				 */
				set_extra_field(gconf, &(stack->prior.extra), NULL);
				set_extra_field(gconf, &(stack->masked.extra), NULL);

				/* And restore source information */
				gconf->source = newsource;
				gconf->scontext = newscontext;
			}

			/* Finish popping the state stack */
			gconf->stack = prev;
			pfree(stack);

			/* Report new value if we changed it */
			if (changed && (gconf->flags & GUC_REPORT))
				ReportGUCOption(gconf);
		}						/* end of stack-popping loop */

		if (stack != NULL)
			still_dirty = true;
	}

	/* If there are no remaining stack entries, we can reset guc_dirty */
	guc_dirty = still_dirty;

	/* Update nesting level */
	GUCNestLevel = nestLevel - 1;
}