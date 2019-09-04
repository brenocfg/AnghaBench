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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConErrResPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  ErrorMessage (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MakeFullPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_ERROR_REQ_PARAM_MISSING ; 
 int /*<<< orphan*/  STRING_MD_ERROR2 ; 
 int /*<<< orphan*/  STRING_MKDIR_HELP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freep (int /*<<< orphan*/ *) ; 
 scalar_t__ nErrorLevel ; 
 int /*<<< orphan*/ * split (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

INT cmd_mkdir (LPTSTR param)
{
    LPTSTR *p;
    INT argc, i;
    if (!_tcsncmp (param, _T("/?"), 2))
    {
        ConOutResPaging(TRUE,STRING_MKDIR_HELP);
        return 0;
    }

    p = split (param, &argc, FALSE, FALSE);
    if (argc == 0)
    {
        ConErrResPuts(STRING_ERROR_REQ_PARAM_MISSING);
        freep(p);
        nErrorLevel = 1;
        return 1;
    }

    nErrorLevel = 0;
    for (i = 0; i < argc; i++)
    {
        if (!MakeFullPath(p[i]))
        {
            if (GetLastError() == ERROR_PATH_NOT_FOUND)
            {
                ConErrResPuts(STRING_MD_ERROR2);
            }
            else
            {
                ErrorMessage (GetLastError(), _T("MD"));
            }
            nErrorLevel = 1;
        }
    }

    freep (p);
    return nErrorLevel;
}