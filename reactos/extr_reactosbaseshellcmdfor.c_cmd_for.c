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
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_FOR_HELP1 ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcsncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugstr_aw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_syntax (int /*<<< orphan*/ ) ; 

INT cmd_for (LPTSTR param)
{
    TRACE ("cmd_for (\'%s\')\n", debugstr_aw(param));

    if (!_tcsncmp (param, _T("/?"), 2))
    {
        ConOutResPaging(TRUE,STRING_FOR_HELP1);
        return 0;
    }

    error_syntax(param);
    return 1;
}