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
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExitBatch () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STRING_EXIT_HELP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _istdigit (int /*<<< orphan*/ ) ; 
 scalar_t__ _istspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ _tcsnicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _ttoi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bExit ; 
 scalar_t__ bc ; 
 int /*<<< orphan*/  nErrorLevel ; 

INT CommandExit(LPTSTR param)
{
    if (!_tcsncmp(param, _T("/?"), 2))
    {
        ConOutResPaging(TRUE, STRING_EXIT_HELP);

        /* Just make sure we don't exit */
        bExit = FALSE;
        return 0;
    }

    if (_tcsnicmp(param, _T("/b"), 2) == 0)
    {
        param += 2;

        /*
         * If a current batch file is running, exit it,
         * otherwise exit this command interpreter instance.
         */
        if (bc)
            ExitBatch();
        else
            bExit = TRUE;
    }
    else
    {
        /* Exit this command interpreter instance */
        bExit = TRUE;
    }

    /* Search for an optional exit code */
    while (_istspace(*param))
        param++;

    /* Set the errorlevel to the exit code */
    if (_istdigit(*param))
        nErrorLevel = _ttoi(param);

    return 0;
}