#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  hMainWnd; int /*<<< orphan*/  hInstance; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HICON ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLIPBRD_ICON ; 
#define  CMD_ABOUT 134 
#define  CMD_AUTOMATIC 133 
#define  CMD_DELETE 132 
#define  CMD_EXIT 131 
#define  CMD_HELP 130 
#define  CMD_OPEN 129 
#define  CMD_SAVE_AS 128 
 int /*<<< orphan*/  DeleteClipboardContent () ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  HtmlHelpW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDYES ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadClipboardFromFile () ; 
 int /*<<< orphan*/  LoadIconW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int MAX_STRING_LEN ; 
 int MB_ICONWARNING ; 
 int MB_YESNO ; 
 int /*<<< orphan*/  MessageBoxRes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_CLIPBOARD ; 
 int /*<<< orphan*/  STRING_DELETE_MSG ; 
 int /*<<< orphan*/  STRING_DELETE_TITLE ; 
 int /*<<< orphan*/  SaveClipboardToFile () ; 
 int /*<<< orphan*/  SetDisplayFormat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShellAboutW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_CLOSE ; 

__attribute__((used)) static int OnCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (LOWORD(wParam))
    {
        case CMD_OPEN:
        {
            LoadClipboardFromFile();
            break;
        }

        case CMD_SAVE_AS:
        {
            SaveClipboardToFile();
            break;
        }

        case CMD_EXIT:
        {
            PostMessageW(Globals.hMainWnd, WM_CLOSE, 0, 0);
            break;
        }

        case CMD_DELETE:
        {
            if (MessageBoxRes(Globals.hMainWnd, Globals.hInstance,
                              STRING_DELETE_MSG, STRING_DELETE_TITLE,
                              MB_ICONWARNING | MB_YESNO) != IDYES)
            {
                break;
            }

            DeleteClipboardContent();
            break;
        }

        case CMD_AUTOMATIC:
        {
            SetDisplayFormat(0);
            break;
        }

        case CMD_HELP:
        {
            HtmlHelpW(Globals.hMainWnd, L"clipbrd.chm", 0, 0);
            break;
        }

        case CMD_ABOUT:
        {
            HICON hIcon;
            WCHAR szTitle[MAX_STRING_LEN];

            hIcon = LoadIconW(Globals.hInstance, MAKEINTRESOURCE(CLIPBRD_ICON));
            LoadStringW(Globals.hInstance, STRING_CLIPBOARD, szTitle, ARRAYSIZE(szTitle));
            ShellAboutW(Globals.hMainWnd, szTitle, NULL, hIcon);
            DeleteObject(hIcon);
            break;
        }

        default:
        {
            break;
        }
    }
    return 0;
}