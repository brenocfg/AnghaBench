#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ofsFilename; int command; int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ WINHELP ;
struct TYPE_4__ {int dwData; TYPE_1__* lpData; } ;
typedef  int LRESULT ;
typedef  int LPSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ COPYDATASTRUCT ;

/* Variables and functions */
#define  HELP_CONTENTS 134 
#define  HELP_CONTEXT 133 
#define  HELP_CONTEXTPOPUP 132 
#define  HELP_FINDER 131 
#define  HELP_HELPONHELP 130 
#define  HELP_QUIT 129 
#define  HELP_SETCONTENTS 128 
 int /*<<< orphan*/  MACRO_Exit () ; 
 int /*<<< orphan*/  MACRO_HelpOn () ; 
 int /*<<< orphan*/  MACRO_JumpContents (char*,char*) ; 
 int /*<<< orphan*/  MACRO_JumpContext (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACRO_JumpHash (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACRO_PopupContext (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACRO_SetContents (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_FIXME (char*,...) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINHELP_HasWorkingWindow () ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 

__attribute__((used)) static LRESULT  WINHELP_HandleCommand(HWND hSrcWnd, LPARAM lParam)
{
    COPYDATASTRUCT*     cds = (COPYDATASTRUCT*)lParam;
    WINHELP*            wh;

    if (cds->dwData != 0xA1DE505)
    {
        WINE_FIXME("Wrong magic number (%08lx)\n", cds->dwData);
        return 0;
    }

    wh = cds->lpData;

    if (wh)
    {
        char*   ptr = (wh->ofsFilename) ? (LPSTR)wh + wh->ofsFilename : NULL;

        WINE_TRACE("Got[%u]: cmd=%u data=%08x fn=%s\n",
                   wh->size, wh->command, wh->data, debugstr_a(ptr));
        switch (wh->command)
        {
        case HELP_CONTEXT:
            if (ptr)
            {
                MACRO_JumpContext(ptr, "main", wh->data);
            }
            if (!WINHELP_HasWorkingWindow()) MACRO_Exit();
            break;
        case HELP_QUIT:
            MACRO_Exit();
            break;
        case HELP_CONTENTS:
            if (ptr)
            {
                MACRO_JumpContents(ptr, "main");
            }
            if (!WINHELP_HasWorkingWindow()) MACRO_Exit();
            break;
        case HELP_HELPONHELP:
            MACRO_HelpOn();
            if (!WINHELP_HasWorkingWindow()) MACRO_Exit();
            break;
        /* case HELP_SETINDEX: */
        case HELP_SETCONTENTS:
            if (ptr)
            {
                MACRO_SetContents(ptr, wh->data);
            }
            break;
        case HELP_CONTEXTPOPUP:
            if (ptr)
            {
                MACRO_PopupContext(ptr, wh->data);
            }
            break;
        /* case HELP_FORCEFILE:*/
        /* case HELP_CONTEXTMENU: */
        case HELP_FINDER:
            /* in fact, should be the topic dialog box */
            WINE_FIXME("HELP_FINDER: stub\n");
            if (ptr)
            {
                MACRO_JumpHash(ptr, "main", 0);
            }
            break;
        /* case HELP_WM_HELP: */
        /* case HELP_SETPOPUP_POS: */
        /* case HELP_KEY: */
        /* case HELP_COMMAND: */
        /* case HELP_PARTIALKEY: */
        /* case HELP_MULTIKEY: */
        /* case HELP_SETWINPOS: */
        default:
            WINE_FIXME("Unhandled command (%x) for remote winhelp control\n", wh->command);
            break;
        }
    }
    /* Always return success for now */
    return 1;
}