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
typedef  scalar_t__* LPTSTR ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_DELAY_HELP ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _tcsncmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ _tcsnicmp (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int _ttoi (scalar_t__*) ; 
 int /*<<< orphan*/  error_req_param_missing () ; 
 scalar_t__ nErrorLevel ; 

INT CommandDelay (LPTSTR param)
{
    DWORD val;
    DWORD mul=1000;

    if (_tcsncmp (param, _T("/?"), 2) == 0)
    {
        ConOutResPaging(TRUE,STRING_DELAY_HELP);
        return 0;
    }

    nErrorLevel = 0;

    if (*param==0)
    {
        error_req_param_missing ();
        return 1;
    }

    if (_tcsnicmp(param,_T("/m"),2) == 0)
    {
        mul = 1;
        param += 2;
    }

    val = _ttoi(param);
    Sleep(val * mul);

    return 0;
}