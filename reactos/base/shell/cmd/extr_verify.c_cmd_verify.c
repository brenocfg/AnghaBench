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
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConErrResPuts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OnOffCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_VERIFY_HELP1 ; 
 int /*<<< orphan*/  STRING_VERIFY_HELP2 ; 
 int /*<<< orphan*/  STRING_VERIFY_HELP3 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bVerify ; 
 int nErrorLevel ; 

INT cmd_verify (LPTSTR param)
{
    if (!_tcsncmp (param, _T("/?"), 2))
    {
        ConOutResPaging(TRUE,STRING_VERIFY_HELP1);
        return 0;
    }

    if (!OnOffCommand(param, &bVerify, STRING_VERIFY_HELP2))
    {
        ConErrResPuts(STRING_VERIFY_HELP3);
        return nErrorLevel = 1;
    }

    return nErrorLevel = 0;
}