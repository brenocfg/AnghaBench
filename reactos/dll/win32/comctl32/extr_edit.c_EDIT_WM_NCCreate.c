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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int style; int bEnableState; char password_char; int buffer_size; int undo_buffer_size; int line_count; struct TYPE_7__* logAttr; scalar_t__ hloc32W; struct TYPE_7__* undo_text; struct TYPE_7__* first_line_def; int /*<<< orphan*/  hwndSelf; void* buffer_limit; int /*<<< orphan*/  hwndParent; int /*<<< orphan*/  hwndListBox; } ;
struct TYPE_6__ {int style; int dwExStyle; int /*<<< orphan*/  hwndParent; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPCREATESTRUCTW ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  LINEDEF ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ EDITSTATE ;

/* Variables and functions */
 void* BUFLIMIT_INITIAL ; 
 int /*<<< orphan*/  EDIT_InvalidateUniscribeData (TYPE_2__*) ; 
 int ES_AUTOHSCROLL ; 
 int ES_AUTOVSCROLL ; 
 int ES_CENTER ; 
 int ES_COMBO ; 
 int ES_LOWERCASE ; 
 int ES_MULTILINE ; 
 int ES_NUMBER ; 
 int ES_PASSWORD ; 
 int ES_RIGHT ; 
 int ES_UPPERCASE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID_CB_LISTBOX ; 
 int LMEM_MOVEABLE ; 
 int LMEM_ZEROINIT ; 
 scalar_t__ LocalAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int LocalSize (scalar_t__) ; 
 int /*<<< orphan*/  ROUND_TO_GROW (int) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_BORDER ; 
 int WS_DISABLED ; 
 int WS_EX_CLIENTEDGE ; 
 int WS_EX_RIGHT ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 
 void* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 

__attribute__((used)) static LRESULT EDIT_WM_NCCreate(HWND hwnd, LPCREATESTRUCTW lpcs)
{
	EDITSTATE *es;
	UINT alloc_size;

    TRACE("Creating edit control, style = %08x\n", lpcs->style);

    if (!(es = heap_alloc_zero(sizeof(*es))))
        return FALSE;
    SetWindowLongPtrW( hwnd, 0, (LONG_PTR)es );

       /*
        *      Note: since the EDITSTATE has not been fully initialized yet,
        *            we can't use any API calls that may send
        *            WM_XXX messages before WM_NCCREATE is completed.
        */

    es->style = lpcs->style;

        es->bEnableState = !(es->style & WS_DISABLED);

	es->hwndSelf = hwnd;
	/* Save parent, which will be notified by EN_* messages */
	es->hwndParent = lpcs->hwndParent;

	if (es->style & ES_COMBO)
	   es->hwndListBox = GetDlgItem(es->hwndParent, ID_CB_LISTBOX);

        /* FIXME: should we handle changes to WS_EX_RIGHT style after creation? */
        if (lpcs->dwExStyle & WS_EX_RIGHT) es->style |= ES_RIGHT;

        /* Number overrides lowercase overrides uppercase (at least it
         * does in Win95).  However I'll bet that ES_NUMBER would be
         * invalid under Win 3.1.
         */
        if (es->style & ES_NUMBER) {
                ; /* do not override the ES_NUMBER */
        }  else if (es->style & ES_LOWERCASE) {
                es->style &= ~ES_UPPERCASE;
        }
	if (es->style & ES_MULTILINE) {
		es->buffer_limit = BUFLIMIT_INITIAL;
		if (es->style & WS_VSCROLL)
			es->style |= ES_AUTOVSCROLL;
		if (es->style & WS_HSCROLL)
			es->style |= ES_AUTOHSCROLL;
		es->style &= ~ES_PASSWORD;
		if ((es->style & ES_CENTER) || (es->style & ES_RIGHT)) {
                        /* Confirmed - RIGHT overrides CENTER */
			if (es->style & ES_RIGHT)
				es->style &= ~ES_CENTER;
			es->style &= ~WS_HSCROLL;
			es->style &= ~ES_AUTOHSCROLL;
		}
	} else {
		es->buffer_limit = BUFLIMIT_INITIAL;
		if ((es->style & ES_RIGHT) && (es->style & ES_CENTER))
			es->style &= ~ES_CENTER;
		es->style &= ~WS_HSCROLL;
		es->style &= ~WS_VSCROLL;
		if (es->style & ES_PASSWORD)
			es->password_char = '*';
	}

	alloc_size = ROUND_TO_GROW((es->buffer_size + 1) * sizeof(WCHAR));
	if(!(es->hloc32W = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, alloc_size)))
	    goto cleanup;
	es->buffer_size = LocalSize(es->hloc32W)/sizeof(WCHAR) - 1;

	if (!(es->undo_text = heap_alloc_zero((es->buffer_size + 1) * sizeof(WCHAR))))
		goto cleanup;
	es->undo_buffer_size = es->buffer_size;

	if (es->style & ES_MULTILINE)
	    if (!(es->first_line_def = heap_alloc_zero(sizeof(LINEDEF))))
	        goto cleanup;
	es->line_count = 1;

	/*
	 * In Win95 look and feel, the WS_BORDER style is replaced by the
	 * WS_EX_CLIENTEDGE style for the edit control. This gives the edit
	 * control a nonclient area so we don't need to draw the border.
         * If WS_BORDER without WS_EX_CLIENTEDGE is specified we shouldn't have
         * a nonclient area and we should handle painting the border ourselves.
         *
         * When making modifications please ensure that the code still works
         * for edit controls created directly with style 0x50800000, exStyle 0
         * (which should have a single pixel border)
	 */
	if (lpcs->dwExStyle & WS_EX_CLIENTEDGE)
		es->style &= ~WS_BORDER;
        else if (es->style & WS_BORDER)
		SetWindowLongW(hwnd, GWL_STYLE, es->style & ~WS_BORDER);

	return TRUE;

cleanup:
	SetWindowLongPtrW(es->hwndSelf, 0, 0);
	EDIT_InvalidateUniscribeData(es);
	heap_free(es->first_line_def);
	heap_free(es->undo_text);
	if (es->hloc32W) LocalFree(es->hloc32W);
	heap_free(es->logAttr);
	heap_free(es);
	return FALSE;
}