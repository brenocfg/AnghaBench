#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  AsciiChar; } ;
struct TYPE_7__ {char wVirtualKeyCode; int dwControlKeyState; TYPE_1__ uChar; } ;
struct TYPE_8__ {TYPE_2__ KeyEvent; } ;
struct TYPE_9__ {TYPE_3__ Event; } ;
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (scalar_t__*) ; 
 int /*<<< orphan*/  AddBreakHandler () ; 
 int /*<<< orphan*/  CMD_ModuleHandle ; 
 int /*<<< orphan*/  ConInDisable () ; 
 int /*<<< orphan*/  ConInEnable () ; 
 int /*<<< orphan*/  ConInKey (TYPE_4__*) ; 
 int /*<<< orphan*/  ConInString (scalar_t__*,int) ; 
 int /*<<< orphan*/  ConOutChar (scalar_t__) ; 
 int /*<<< orphan*/  ConOutResPrintf (scalar_t__) ; 
 int LEFT_CTRL_PRESSED ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROMPT_BREAK ; 
 int /*<<< orphan*/  PROMPT_NO ; 
 int /*<<< orphan*/  PROMPT_YES ; 
 int RC_STRING_MAX_SIZE ; 
 int RIGHT_CTRL_PRESSED ; 
 int /*<<< orphan*/  RemoveBreakHandler () ; 
 int /*<<< orphan*/  STRING_CHOICE_OPTION ; 
 char VK_CONTROL ; 
 char VK_ESCAPE ; 
 char VK_MENU ; 
 char VK_SHIFT ; 
 scalar_t__ _T (char) ; 
 scalar_t__ _istspace (scalar_t__) ; 
 int /*<<< orphan*/ * _tcschr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _tcsncmp (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  _tcsupr (scalar_t__*) ; 
 int /*<<< orphan*/ * _totlower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cKey ; 
 TYPE_4__ ir ; 
 int /*<<< orphan*/  szKeys ; 

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