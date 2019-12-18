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
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_INPUT ; 
 int CMDLINE_LENGTH ; 
 scalar_t__ CheckCtrlBreak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutChar (scalar_t__) ; 
 int /*<<< orphan*/  ConOutResPrintf (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PrintPrompt () ; 
 scalar_t__* ReadBatchLine () ; 
 int /*<<< orphan*/  ReadCommand (scalar_t__*,int) ; 
 int /*<<< orphan*/  STRING_MORE ; 
 scalar_t__ SubstituteVars (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _T (char) ; 
 scalar_t__ bEcho ; 
 int /*<<< orphan*/  bExit ; 
 int /*<<< orphan*/  bIgnoreEcho ; 
 int /*<<< orphan*/ * bc ; 

BOOL
ReadLine(TCHAR *commandline, BOOL bMore)
{
    TCHAR readline[CMDLINE_LENGTH];
    LPTSTR ip;

    /* if no batch input then... */
    if (bc == NULL)
    {
        if (bMore)
        {
            ConOutResPrintf(STRING_MORE);
        }
        else
        {
            /* JPP 19980807 - if echo off, don't print prompt */
            if (bEcho)
            {
                if (!bIgnoreEcho)
                    ConOutChar(_T('\n'));
                PrintPrompt();
            }
        }

        if (!ReadCommand(readline, CMDLINE_LENGTH - 1))
        {
            bExit = TRUE;
            return FALSE;
        }

        if (readline[0] == _T('\0'))
            ConOutChar(_T('\n'));

        if (CheckCtrlBreak(BREAK_INPUT))
            return FALSE;

        if (readline[0] == _T('\0'))
            return FALSE;

        ip = readline;
    }
    else
    {
        ip = ReadBatchLine();
        if (!ip)
            return FALSE;
    }

    return SubstituteVars(ip, commandline, _T('%'));
}