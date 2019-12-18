#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ optc; scalar_t__ argc; } ;
struct TYPE_10__ {TYPE_1__* opts; } ;
struct TYPE_9__ {int /*<<< orphan*/  parsed; TYPE_5__* opt_args; TYPE_5__ glb_args; } ;
struct TYPE_8__ {int index; int /*<<< orphan*/ * p_next; } ;
struct TYPE_7__ {int flags; scalar_t__ max; scalar_t__ min; } ;
typedef  TYPE_2__ CMDLINE_ARG ;

/* Variables and functions */
 int CMDLINE_ERR_ERROR ; 
 int CMDLINE_ERR_FEWARG ; 
 int CMDLINE_ERR_ILLOPT ; 
 int CMDLINE_ERR_INVKEY ; 
 int CMDLINE_ERR_MANYARG ; 
 int CMDLINE_ERR_NOMEM ; 
 int CMDLINE_ERR_OK ; 
 int CMDLINE_ERR_OPTMIS ; 
 int CMDLINE_OPTFLAG_ALLOW ; 
 int CMDLINE_OPTFLAG_MANDAT ; 
 int /*<<< orphan*/  CMDLINE_TRUE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cmdline_argadd (TYPE_5__*,TYPE_2__*) ; 
 TYPE_4__ cmdline_cfg ; 
 TYPE_3__ cmdline_data ; 
 int strlen (char*) ; 

int cmdline_read(int argc, char* argv[])
{
	int i, option=0;

	/* Process every command line argument in argv[] array */
	for( i = 1; i < argc; i++ )
	{
		/* Does the argument start with a dash? */
		if( *argv[i] == '-' )
		{
			/* The argument must be two characters: a dash, and a letter */
			if( strlen(argv[i]) != 2 )
			{
				/* ERROR: option syntax (needs to be a dash and one letter) */
				return(CMDLINE_ERR_ERROR);
			}

			/* Check validity of the option key ('a' through 'z') */
			if( ((*(argv[i] + 1)) < 'a') || ((*(argv[i] + 1)) > 'z') )
			{
				/* ERROR: option sysntax (invalid option key) */
				return(CMDLINE_ERR_INVKEY);
			}

			/* Calculate the option index */
			option = (*(argv[i] + 1)) - 'a';
			if((option < 0) || (option > 25)) return(CMDLINE_ERR_INVKEY);

			/* Check to see if the option is allowed */
			if( cmdline_cfg.opts[option].flags & CMDLINE_OPTFLAG_ALLOW )
			{
				/* Option allowed. */
				cmdline_data.opt_args[option].optc++;
				continue;
			}
			else
			{
				/* ERROR: Option is not allowed */
				return(CMDLINE_ERR_ILLOPT);
			}
		}
		else
		{
			/* Read the arguments for the option */
			CMDLINE_ARG*	p_arg;

			/* Allocate space for the argument node */
			p_arg = (CMDLINE_ARG*)calloc(1,sizeof(CMDLINE_ARG));
			if( p_arg== NULL )
			{
				/* ERROR: Can't allocate memory for the argument index */
				return(CMDLINE_ERR_NOMEM);
			}

			/* Initialize the argument */
			p_arg->index	= i;
			p_arg->p_next	= NULL;

			/* Check if we can add to the list of arguments for this option */
			if( (option < 0)																/* Do we have to add to the global list? */
				|| (cmdline_data.opt_args[option].argc == cmdline_cfg.opts[option].max)		/* Did we reach MAX arguments? */
				)
			{
				/* This option does not require arguments. Keep the argument in the global list. */
				cmdline_argadd(&(cmdline_data.glb_args), p_arg);
				continue;
			}
			else
			{
				/* See if the current count has reached max for this option */
				if( cmdline_data.opt_args[option].argc == cmdline_cfg.opts[option].max )
				{
					/* ERROR: too many arguments for an option */
					return(CMDLINE_ERR_MANYARG);
				}
				else
				{
					/* Link the argument to the arg list of the option */
					cmdline_argadd(&(cmdline_data.opt_args[option]), p_arg);
					continue;
				}
			}
		}
	}

	/* ****** We read the complete command line. See if what we collected matches the configuration ******* */

	/* Check every collected option against its configuration */
	for( i=0; i < 26; i++ )
	{
		/* Check if this option was allowed */
		if(cmdline_cfg.opts[i].flags & CMDLINE_OPTFLAG_ALLOW)
		{
			/* See if it was mandatory */
			if(cmdline_cfg.opts[i].flags & CMDLINE_OPTFLAG_MANDAT)
			{
				/* Check if we really collected this option on the command line. */
				if(cmdline_data.opt_args[i].optc == 0)
				{
					/* ERROR: a missing mandatory option */
					return(CMDLINE_ERR_OPTMIS);
				}
				else
				{
					/* Option was there. Check how many args we got for it. */
					if(cmdline_data.opt_args[i].argc < cmdline_cfg.opts[i].min)
					{
						/* ERROR: too few arguments for an option */
						return(CMDLINE_ERR_FEWARG);
					}
					else
					{
						/* This mandatory option was proper. */
						continue;
					}
				}
			}
			else	/* This is non-mandatory option: */
			{
				/* Check if the option was specified on the command line */
				if(cmdline_data.opt_args[i].optc == 0)
				{
					/* option wasn't specified, go to the next */
					continue;
				}
				else
				{
					/* Option was there. Check how many args we collected for it. */
					if(cmdline_data.opt_args[i].argc < cmdline_cfg.opts[i].min)
					{
						/* ERROR: too few arguments for a non-mandatory option */
						return(CMDLINE_ERR_FEWARG);
					}
					else
					{
						/* This non-mandatory option was proper. */
						continue;
					}
				}
			}
		}
		else	/* Option was not allowed. */
		{
			/* We should not get here as the non-allowed options should have been
			trapped eariler. */
		}
	}

	/* Command line was proper as far as the number of options and their arguments */
	cmdline_data.parsed = CMDLINE_TRUE;
	return(CMDLINE_ERR_OK);
}