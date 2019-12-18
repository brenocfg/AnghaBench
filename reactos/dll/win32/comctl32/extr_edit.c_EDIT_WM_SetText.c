#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int flags; int style; scalar_t__ hwndListBox; scalar_t__ x_offset; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_InvalidateUniscribeData (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_NOTIFY_PARENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_UpdateScrollInfo (TYPE_1__*) ; 
 int EF_MODIFIED ; 
 int EF_UPDATE ; 
 int /*<<< orphan*/  EN_CHANGE ; 
 int /*<<< orphan*/  EN_UPDATE ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void EDIT_WM_SetText(EDITSTATE *es, LPCWSTR text)
{
    if (es->flags & EF_UPDATE)
        /* fixed this bug once; complain if we see it about to happen again. */
        ERR("SetSel may generate UPDATE message whose handler may reset "
            "selection.\n");

    EDIT_EM_SetSel(es, 0, (UINT)-1, FALSE);
    if (text)
    {
	TRACE("%s\n", debugstr_w(text));
	EDIT_EM_ReplaceSel(es, FALSE, text, strlenW(text), FALSE, FALSE);
    }
    else
    {
	TRACE("<NULL>\n");
	EDIT_EM_ReplaceSel(es, FALSE, NULL, 0, FALSE, FALSE);
    }
    es->x_offset = 0;
    es->flags &= ~EF_MODIFIED;
    EDIT_EM_SetSel(es, 0, 0, FALSE);

    /* Send the notification after the selection start and end have been set
     * edit control doesn't send notification on WM_SETTEXT
     * if it is multiline, or it is part of combobox
     */
    if( !((es->style & ES_MULTILINE) || es->hwndListBox))
    {
        EDIT_NOTIFY_PARENT(es, EN_UPDATE);
        EDIT_NOTIFY_PARENT(es, EN_CHANGE);
    }
    EDIT_EM_ScrollCaret(es);
    EDIT_UpdateScrollInfo(es);
    EDIT_InvalidateUniscribeData(es);
}