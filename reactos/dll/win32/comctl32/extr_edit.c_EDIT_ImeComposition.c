#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ composition_len; scalar_t__ selection_start; scalar_t__ selection_end; scalar_t__ composition_start; int flags; } ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HIMC ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_GetCompositionStr (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_GetResultStr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_SetCaretPos (TYPE_1__*,scalar_t__,int) ; 
 int EF_AFTER_WRAP ; 
 int GCS_COMPSTR ; 
 int /*<<< orphan*/  GCS_CURSORPOS ; 
 int GCS_RESULTSTR ; 
 int ImmGetCompositionStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImmGetContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImmReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void EDIT_ImeComposition(HWND hwnd, LPARAM CompFlag, EDITSTATE *es)
{
    HIMC hIMC;
    int cursor;

    if (es->composition_len == 0 && es->selection_start != es->selection_end)
    {
        EDIT_EM_ReplaceSel(es, TRUE, NULL, 0, TRUE, TRUE);
        es->composition_start = es->selection_end;
    }

    hIMC = ImmGetContext(hwnd);
    if (!hIMC)
        return;

    if (CompFlag & GCS_RESULTSTR)
    {
        EDIT_GetResultStr(hIMC, es);
        cursor = 0;
    }
    else
    {
        if (CompFlag & GCS_COMPSTR)
            EDIT_GetCompositionStr(hIMC, CompFlag, es);
        cursor = ImmGetCompositionStringW(hIMC, GCS_CURSORPOS, 0, 0);
    }
    ImmReleaseContext(hwnd, hIMC);
    EDIT_SetCaretPos(es, es->selection_start + cursor, es->flags & EF_AFTER_WRAP);
}