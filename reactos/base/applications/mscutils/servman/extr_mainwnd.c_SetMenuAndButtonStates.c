#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {scalar_t__ dwStartType; } ;
struct TYPE_10__ {scalar_t__ SelectedItem; int /*<<< orphan*/  hTool; int /*<<< orphan*/  hShortcutMenu; TYPE_2__* pCurrentService; scalar_t__ bIsUserAnAdmin; int /*<<< orphan*/  hMainWnd; } ;
struct TYPE_8__ {scalar_t__ dwControlsAccepted; scalar_t__ dwCurrentState; } ;
struct TYPE_9__ {int /*<<< orphan*/  lpServiceName; TYPE_1__ ServiceStatusProcess; } ;
typedef  TYPE_3__* PMAIN_WND_INFO ;
typedef  TYPE_4__* LPQUERY_SERVICE_CONFIG ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* GetServiceConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ ID_DELETE ; 
 scalar_t__ ID_PAUSE ; 
 scalar_t__ ID_PROP ; 
 scalar_t__ ID_RESTART ; 
 scalar_t__ ID_START ; 
 scalar_t__ ID_STOP ; 
 scalar_t__ MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MF_ENABLED ; 
 int /*<<< orphan*/  MF_GRAYED ; 
 scalar_t__ NO_ITEM_SELECTED ; 
 scalar_t__ SERVICE_ACCEPT_PAUSE_CONTINUE ; 
 scalar_t__ SERVICE_ACCEPT_STOP ; 
 scalar_t__ SERVICE_DISABLED ; 
 scalar_t__ SERVICE_RUNNING ; 
 scalar_t__ SERVICE_STOPPED ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBSTATE_ENABLED ; 
 int /*<<< orphan*/  TBSTATE_INDETERMINATE ; 
 int /*<<< orphan*/  TB_SETSTATE ; 

VOID SetMenuAndButtonStates(PMAIN_WND_INFO Info)
{
    HMENU hMainMenu;
    UINT i;

    /* get handle to menu */
    hMainMenu = GetMenu(Info->hMainWnd);

    /* set all to greyed */
    for (i = ID_START; i <= ID_RESTART; i++)
    {
        EnableMenuItem(hMainMenu, i, MF_GRAYED);
        EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0), i, MF_GRAYED);
        SendMessage(Info->hTool, TB_SETSTATE, i,
                    (LPARAM)MAKELONG(TBSTATE_INDETERMINATE, 0));
    }

    if (Info->SelectedItem != NO_ITEM_SELECTED)
    {
        LPQUERY_SERVICE_CONFIG lpServiceConfig = NULL;
        DWORD Flags, State;

        /* allow user to delete service */
        if (Info->bIsUserAnAdmin)
        {
            SendMessage(Info->hTool, TB_SETSTATE, ID_DELETE,
                       (LPARAM)MAKELONG(TBSTATE_ENABLED, 0));
            EnableMenuItem(hMainMenu, ID_DELETE, MF_ENABLED);
            EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0), ID_DELETE, MF_ENABLED);
        }

        Flags = Info->pCurrentService->ServiceStatusProcess.dwControlsAccepted;
        State = Info->pCurrentService->ServiceStatusProcess.dwCurrentState;

        lpServiceConfig = GetServiceConfig(Info->pCurrentService->lpServiceName);

        if (lpServiceConfig && lpServiceConfig->dwStartType != SERVICE_DISABLED)
        {
            if (State == SERVICE_STOPPED)
            {
                EnableMenuItem(hMainMenu, ID_START, MF_ENABLED);
                EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0), ID_START, MF_ENABLED);
                SendMessage(Info->hTool, TB_SETSTATE, ID_START,
                       (LPARAM)MAKELONG(TBSTATE_ENABLED, 0));
            }

            if ( (Flags & SERVICE_ACCEPT_STOP) && (State == SERVICE_RUNNING) )
            {
                EnableMenuItem(hMainMenu, ID_RESTART, MF_ENABLED);
                EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0), ID_RESTART, MF_ENABLED);
                SendMessage(Info->hTool, TB_SETSTATE, ID_RESTART,
                       (LPARAM)MAKELONG(TBSTATE_ENABLED, 0));
            }
        }

        if(lpServiceConfig)
            HeapFree(GetProcessHeap(), 0, lpServiceConfig);

        if ( (Flags & SERVICE_ACCEPT_STOP) && (State == SERVICE_RUNNING) )
        {
            EnableMenuItem(hMainMenu, ID_STOP, MF_ENABLED);
            EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0), ID_STOP, MF_ENABLED);
            SendMessage(Info->hTool, TB_SETSTATE, ID_STOP,
                   (LPARAM)MAKELONG(TBSTATE_ENABLED, 0));
        }

        if ( (Flags & SERVICE_ACCEPT_PAUSE_CONTINUE) && (State == SERVICE_RUNNING) )
        {
            EnableMenuItem(hMainMenu, ID_PAUSE, MF_ENABLED);
            EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0), ID_PAUSE, MF_ENABLED);
            SendMessage(Info->hTool, TB_SETSTATE, ID_PAUSE,
                   (LPARAM)MAKELONG(TBSTATE_ENABLED, 0));
        }
    }
    else
    {
        /* disable tools which rely on a selected service */
        EnableMenuItem(hMainMenu, ID_PROP, MF_GRAYED);
        EnableMenuItem(hMainMenu, ID_DELETE, MF_GRAYED);
        EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0), ID_PROP, MF_GRAYED);
        EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0), ID_DELETE, MF_GRAYED);
        SendMessage(Info->hTool, TB_SETSTATE, ID_PROP,
                   (LPARAM)MAKELONG(TBSTATE_INDETERMINATE, 0));
        SendMessage(Info->hTool, TB_SETSTATE, ID_DELETE,
                   (LPARAM)MAKELONG(TBSTATE_INDETERMINATE, 0));
    }

}