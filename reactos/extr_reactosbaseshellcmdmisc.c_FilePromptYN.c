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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMD_ModuleHandle ; 
 int /*<<< orphan*/  ConInString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ConOutChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutResPrintf (scalar_t__) ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROMPT_NO ; 
 int /*<<< orphan*/  PROMPT_YES ; 
 int RC_STRING_MAX_SIZE ; 
 int /*<<< orphan*/  STRING_CHOICE_OPTION ; 
 int /*<<< orphan*/  _T (char) ; 
 scalar_t__ _istspace (int /*<<< orphan*/ ) ; 
 scalar_t__ _tcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _tcsupr (int /*<<< orphan*/ *) ; 

INT FilePromptYN (UINT resID)
{
    TCHAR szMsg[RC_STRING_MAX_SIZE];
//  TCHAR cKey = 0;
//  LPTSTR szKeys = _T("yna");

    TCHAR szIn[10];
    LPTSTR p;

    if (resID != 0)
        ConOutResPrintf (resID);

    /* preliminary fix */
    ConInString(szIn, 10);
    ConOutChar(_T('\n'));

    _tcsupr (szIn);
    for (p = szIn; _istspace (*p); p++)
        ;

    LoadString(CMD_ModuleHandle, STRING_CHOICE_OPTION, szMsg, ARRAYSIZE(szMsg));

    if (_tcsncmp(p, &szMsg[0], 1) == 0)
        return PROMPT_YES;
    else if (_tcsncmp(p, &szMsg[1], 1) == 0)
        return PROMPT_NO;
#if 0
    else if (*p == _T('\03'))
        return PROMPT_BREAK;
#endif

    return PROMPT_NO;

    /* unfinished solution */
#if 0
    RemoveBreakHandler();
    ConInDisable();

    do
    {
        ConInKey (&ir);
        cKey = _totlower (ir.Event.KeyEvent.uChar.AsciiChar);
        if (_tcschr (szKeys, cKey[0]) == NULL)
            cKey = 0;


    }
    while ((ir.Event.KeyEvent.wVirtualKeyCode == VK_SHIFT) ||
           (ir.Event.KeyEvent.wVirtualKeyCode == VK_MENU) ||
           (ir.Event.KeyEvent.wVirtualKeyCode == VK_CONTROL));

    AddBreakHandler();
    ConInEnable();

    if ((ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) ||
        ((ir.Event.KeyEvent.wVirtualKeyCode == 'C') &&
         (ir.Event.KeyEvent.dwControlKeyState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED))))
        return PROMPT_BREAK;

    return PROMPT_YES;
#endif
}