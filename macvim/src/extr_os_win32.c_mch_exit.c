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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetConsoleCursorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetConsoleIcon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMODE_COOK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dyn_libintl_end () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdDump ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_cci ; 
 int /*<<< orphan*/  g_cmodein ; 
 int /*<<< orphan*/  g_cmodeout ; 
 scalar_t__ g_fCanChangeIcon ; 
 int /*<<< orphan*/  g_fForceExit ; 
 scalar_t__ g_fWindInitCalled ; 
 int /*<<< orphan*/  g_hConIn ; 
 int /*<<< orphan*/  g_hConOut ; 
 int /*<<< orphan*/  g_hOrigIcon ; 
 int /*<<< orphan*/  g_hOrigIconSmall ; 
 int /*<<< orphan*/  g_hWnd ; 
 int /*<<< orphan*/  mch_restore_title (int) ; 
 int /*<<< orphan*/  ml_close_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoptermcap () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
mch_exit(int r)
{
    stoptermcap();

    if (g_fWindInitCalled)
	settmode(TMODE_COOK);

    ml_close_all(TRUE);		/* remove all memfiles */

    if (g_fWindInitCalled)
    {
#ifdef FEAT_TITLE
	mch_restore_title(3);
	/*
	 * Restore both the small and big icons of the console window to
	 * what they were at startup.  Don't do this when the window is
	 * closed, Vim would hang here.
	 */
	if (g_fCanChangeIcon && !g_fForceExit)
	    SetConsoleIcon(g_hWnd, g_hOrigIconSmall, g_hOrigIcon);
#endif

#ifdef MCH_WRITE_DUMP
	if (fdDump)
	{
	    time_t t;

	    time(&t);
	    fputs(ctime(&t), fdDump);
	    fclose(fdDump);
	}
	fdDump = NULL;
#endif
    }

    SetConsoleCursorInfo(g_hConOut, &g_cci);
    SetConsoleMode(g_hConIn,  g_cmodein);
    SetConsoleMode(g_hConOut, g_cmodeout);

#ifdef DYNAMIC_GETTEXT
    dyn_libintl_end();
#endif

    exit(r);
}