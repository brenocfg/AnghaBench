#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hAddressBarWnd; scalar_t__ hWnd; } ;
struct TYPE_4__ {scalar_t__ message; scalar_t__ hwnd; int wParam; } ;
typedef  TYPE_1__* PMSG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetKeyState (int /*<<< orphan*/ ) ; 
 scalar_t__ GetParent (scalar_t__) ; 
 int /*<<< orphan*/  ID_SWITCH_PANELS ; 
 int /*<<< orphan*/  PostMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VK_CONTROL ; 
 int VK_TAB ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 scalar_t__ WM_KEYDOWN ; 
 TYPE_2__* g_pChildWnd ; 

BOOL TranslateChildTabMessage(PMSG msg)
{
    if (msg->message != WM_KEYDOWN) return FALSE;

    /* Allow Ctrl+A on address bar */
    if ((msg->hwnd == g_pChildWnd->hAddressBarWnd) &&
        (msg->message == WM_KEYDOWN) &&
        (msg->wParam == L'A') && (GetKeyState(VK_CONTROL) < 0))
    {
        SendMessageW(msg->hwnd, EM_SETSEL, 0, -1);
        return TRUE;
    }

    if (msg->wParam != VK_TAB) return FALSE;
    if (GetParent(msg->hwnd) != g_pChildWnd->hWnd) return FALSE;
    PostMessageW(g_pChildWnd->hWnd, WM_COMMAND, ID_SWITCH_PANELS, 0);
    return TRUE;
}