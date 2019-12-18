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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ UI ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
#define  UI_CTRL_IS_REDOABLE 129 
#define  UI_CTRL_PRINT_ERRORS 128 
 int UI_FLAG_PRINT_ERRORS ; 
 int UI_FLAG_REDOABLE ; 
 int /*<<< orphan*/  UI_F_UI_CTRL ; 
 int /*<<< orphan*/  UI_R_UNKNOWN_CONTROL_COMMAND ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int UI_ctrl(UI *ui, int cmd, long i, void *p, void (*f) (void))
{
    if (ui == NULL) {
        UIerr(UI_F_UI_CTRL, ERR_R_PASSED_NULL_PARAMETER);
        return -1;
    }
    switch (cmd) {
    case UI_CTRL_PRINT_ERRORS:
        {
            int save_flag = ! !(ui->flags & UI_FLAG_PRINT_ERRORS);
            if (i)
                ui->flags |= UI_FLAG_PRINT_ERRORS;
            else
                ui->flags &= ~UI_FLAG_PRINT_ERRORS;
            return save_flag;
        }
    case UI_CTRL_IS_REDOABLE:
        return ! !(ui->flags & UI_FLAG_REDOABLE);
    default:
        break;
    }
    UIerr(UI_F_UI_CTRL, UI_R_UNKNOWN_CONTROL_COMMAND);
    return -1;
}