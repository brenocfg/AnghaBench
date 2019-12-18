#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  hwndParent; scalar_t__ hWnd; } ;
struct TYPE_5__ {int /*<<< orphan*/  idFrom; int /*<<< orphan*/  code; scalar_t__ hwndFrom; } ;
struct TYPE_6__ {void* wParam; int /*<<< orphan*/  lParam; TYPE_1__ nmhdr; int /*<<< orphan*/  msg; } ;
typedef  TYPE_2__ MSGFILTER ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EN_MSGFILTER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_NOTIFY ; 

__attribute__((used)) static BOOL
ME_FilterEvent(ME_TextEditor *editor, UINT msg, WPARAM* wParam, LPARAM* lParam)
{
    MSGFILTER msgf;

    if (!editor->hWnd || !editor->hwndParent) return FALSE;
    msgf.nmhdr.hwndFrom = editor->hWnd;
    msgf.nmhdr.idFrom = GetWindowLongW(editor->hWnd, GWLP_ID);
    msgf.nmhdr.code = EN_MSGFILTER;
    msgf.msg = msg;
    msgf.wParam = *wParam;
    msgf.lParam = *lParam;
    if (SendMessageW(editor->hwndParent, WM_NOTIFY, msgf.nmhdr.idFrom, (LPARAM)&msgf))
        return FALSE;
    *wParam = msgf.wParam;
    *lParam = msgf.lParam;
    msgf.wParam = *wParam;

    return TRUE;
}