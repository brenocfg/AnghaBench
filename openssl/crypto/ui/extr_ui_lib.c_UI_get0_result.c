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
struct TYPE_3__ {int /*<<< orphan*/  strings; } ;
typedef  TYPE_1__ UI ;

/* Variables and functions */
 int /*<<< orphan*/  UI_F_UI_GET0_RESULT ; 
 int /*<<< orphan*/  UI_R_INDEX_TOO_LARGE ; 
 int /*<<< orphan*/  UI_R_INDEX_TOO_SMALL ; 
 char const* UI_get0_result_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sk_UI_STRING_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_UI_STRING_value (int /*<<< orphan*/ ,int) ; 

const char *UI_get0_result(UI *ui, int i)
{
    if (i < 0) {
        UIerr(UI_F_UI_GET0_RESULT, UI_R_INDEX_TOO_SMALL);
        return NULL;
    }
    if (i >= sk_UI_STRING_num(ui->strings)) {
        UIerr(UI_F_UI_GET0_RESULT, UI_R_INDEX_TOO_LARGE);
        return NULL;
    }
    return UI_get0_result_string(sk_UI_STRING_value(ui->strings, i));
}