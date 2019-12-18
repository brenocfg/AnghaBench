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
struct TYPE_2__ {int /*<<< orphan*/  vars; } ;

/* Variables and functions */
 char* GetVariable (int /*<<< orphan*/ ,char*) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PSQLHISTORY ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_history () ; 
 int /*<<< orphan*/  expand_tilde (scalar_t__*) ; 
 int /*<<< orphan*/  finishInput ; 
 scalar_t__ get_home_path (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ history_lines_added ; 
 int /*<<< orphan*/  initialize_readline () ; 
 scalar_t__ pg_strdup (char const*) ; 
 TYPE_1__ pset ; 
 scalar_t__ psprintf (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ psql_history ; 
 int /*<<< orphan*/  read_history (scalar_t__) ; 
 int /*<<< orphan*/  rl_initialize () ; 
 scalar_t__ strlen (char*) ; 
 int useHistory ; 
 int useReadline ; 
 int /*<<< orphan*/  using_history () ; 

void
initializeInput(int flags)
{
#ifdef USE_READLINE
	if (flags & 1)
	{
		const char *histfile;
		char		home[MAXPGPATH];

		useReadline = true;

		/* these two things must be done in this order: */
		initialize_readline();
		rl_initialize();

		useHistory = true;
		using_history();
		history_lines_added = 0;

		histfile = GetVariable(pset.vars, "HISTFILE");

		if (histfile == NULL)
		{
			char	   *envhist;

			envhist = getenv("PSQL_HISTORY");
			if (envhist != NULL && strlen(envhist) > 0)
				histfile = envhist;
		}

		if (histfile == NULL)
		{
			if (get_home_path(home))
				psql_history = psprintf("%s/%s", home, PSQLHISTORY);
		}
		else
		{
			psql_history = pg_strdup(histfile);
			expand_tilde(&psql_history);
		}

		if (psql_history)
		{
			read_history(psql_history);
			decode_history();
		}
	}
#endif

	atexit(finishInput);
}