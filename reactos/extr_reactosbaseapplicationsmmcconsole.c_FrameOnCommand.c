#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  hMenuConsoleLarge; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__* PCONSOLE_MAINFRAME_WND ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CreateNewMDIChild (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefFrameProc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrameOnSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrameOnSaveAs (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IDM_FILE_EXIT 131 
#define  IDM_FILE_NEW 130 
#define  IDM_FILE_SAVE 129 
#define  IDM_FILE_SAVEAS 128 
 int IDM_MDI_FIRSTCHILD ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_CLOSE ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 int /*<<< orphan*/  hwndMDIClient ; 

__attribute__((used)) static VOID
FrameOnCommand(HWND hwnd,
               UINT uMsg,
               WPARAM wParam,
               LPARAM lParam)
{
    PCONSOLE_MAINFRAME_WND Info;
    HWND hChild;

    Info = (PCONSOLE_MAINFRAME_WND)GetWindowLongPtr(hwnd, 0);

    switch (LOWORD(wParam))
    {
        case IDM_FILE_NEW:
            CreateNewMDIChild(Info, hwndMDIClient);
            SetMenu(Info->hwnd,
                    Info->hMenuConsoleLarge);
            break;

        case IDM_FILE_SAVE:
            FrameOnSave(hwnd);
            break;

        case IDM_FILE_SAVEAS:
            FrameOnSaveAs(hwnd);
            break;

        case IDM_FILE_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;

        default:
            if (LOWORD(wParam) >= IDM_MDI_FIRSTCHILD)
            {
                DefFrameProc(hwnd, hwndMDIClient, uMsg, wParam, lParam);
            }
            else
            {
                hChild = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0);
                if (hChild)
                {
                    SendMessage(hChild, WM_COMMAND, wParam, lParam);
                }
            }
            break;
    }
}