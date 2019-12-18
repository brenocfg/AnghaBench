#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ selection_end; scalar_t__ composition_start; scalar_t__ selection_start; scalar_t__ composition_len; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HIMC ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GCS_RESULTSTR ; 
 int ImmGetCompositionStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void EDIT_GetResultStr(HIMC hIMC, EDITSTATE *es)
{
    LONG buflen;
    LPWSTR lpResultStr;

    buflen = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);
    if (buflen <= 0)
    {
        return;
    }

    lpResultStr = heap_alloc(buflen);
    if (!lpResultStr)
    {
        ERR("Unable to alloc buffer for IME string\n");
        return;
    }

    ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, lpResultStr, buflen);

    /* check for change in composition start */
    if (es->selection_end < es->composition_start)
        es->composition_start = es->selection_end;

    es->selection_start = es->composition_start;
    es->selection_end = es->composition_start + es->composition_len;
    EDIT_EM_ReplaceSel(es, TRUE, lpResultStr, buflen / sizeof(WCHAR), TRUE, TRUE);
    es->composition_start = es->selection_end;
    es->composition_len = 0;

    heap_free(lpResultStr);
}