#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* page; int /*<<< orphan*/  hBrush; scalar_t__ hHistoryWnd; scalar_t__ origRicheditWndProc; int /*<<< orphan*/  hMainWnd; TYPE_1__* info; struct TYPE_10__* next; } ;
typedef  TYPE_2__ WINHELP_WINDOW ;
struct TYPE_12__ {int wVersion; TYPE_2__* win_list; TYPE_2__* active_popup; TYPE_2__* active_win; } ;
struct TYPE_11__ {int /*<<< orphan*/  file; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_ID_TEXT ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  GWLP_WNDPROC ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_8__ Globals ; 
 int /*<<< orphan*/  HLPFILE_FreeHlpFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MACRO_Exit () ; 
 int /*<<< orphan*/  PostQuitMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetActiveWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINHELP_DeleteBackSet (TYPE_2__*) ; 
 int /*<<< orphan*/  WINHELP_DeleteButtons (TYPE_2__*) ; 
 int /*<<< orphan*/  WINHELP_DeletePageLinks (TYPE_4__*) ; 
 int /*<<< orphan*/  lstrcmpiA (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void WINHELP_DeleteWindow(WINHELP_WINDOW* win)
{
    WINHELP_WINDOW**    w;
    BOOL bExit;
    HWND hTextWnd;

    for (w = &Globals.win_list; *w; w = &(*w)->next)
    {
        if (*w == win)
        {
            *w = win->next;
            break;
        }
    }
    bExit = (Globals.wVersion >= 4 && !lstrcmpiA(win->info->name, "main"));

    if (Globals.active_win == win)
    {
        Globals.active_win = Globals.win_list;
        if (Globals.win_list)
            SetActiveWindow(Globals.win_list->hMainWnd);
    }

    if (win == Globals.active_popup)
        Globals.active_popup = NULL;

    hTextWnd = GetDlgItem(win->hMainWnd, CTL_ID_TEXT);
    SetWindowLongPtrA(hTextWnd, GWLP_WNDPROC, (LONG_PTR)win->origRicheditWndProc);

    WINHELP_DeleteButtons(win);

    if (win->page) WINHELP_DeletePageLinks(win->page);
    if (win->hHistoryWnd) DestroyWindow(win->hHistoryWnd);

    DeleteObject(win->hBrush);

    WINHELP_DeleteBackSet(win);

    if (win->page) HLPFILE_FreeHlpFile(win->page->file);
    HeapFree(GetProcessHeap(), 0, win);

    if (bExit) MACRO_Exit();
    if (!Globals.win_list)
        PostQuitMessage(0);
}