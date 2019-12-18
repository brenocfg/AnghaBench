#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hwndParent; } ;
struct TYPE_6__ {int exStyleFlags; int styleFlags; int /*<<< orphan*/  hwndParent; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  ITextHost ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ CREATESTRUCTW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ES_WANTRETURN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ME_CreateTextHost (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ME_MakeEditor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL create_windowed_editor(HWND hwnd, CREATESTRUCTW *create, BOOL emulate_10)
{
    ITextHost *host = ME_CreateTextHost( hwnd, create, emulate_10 );
    ME_TextEditor *editor;

    if (!host) return FALSE;

    editor = ME_MakeEditor( host, emulate_10 );
    if (!editor)
    {
        ITextHost_Release( host );
        return FALSE;
    }

    editor->exStyleFlags = GetWindowLongW( hwnd, GWL_EXSTYLE );
    editor->styleFlags |= GetWindowLongW( hwnd, GWL_STYLE ) & ES_WANTRETURN;
    editor->hWnd = hwnd; /* FIXME: Remove editor's dependence on hWnd */
    editor->hwndParent = create->hwndParent;

    SetWindowLongPtrW( hwnd, 0, (LONG_PTR)editor );

    return TRUE;
}