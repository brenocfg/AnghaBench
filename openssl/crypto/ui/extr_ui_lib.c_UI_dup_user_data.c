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
struct TYPE_7__ {int /*<<< orphan*/  flags; TYPE_1__* meth; } ;
typedef  TYPE_2__ UI ;
struct TYPE_6__ {void* (* ui_duplicate_data ) (TYPE_2__*,void*) ;int /*<<< orphan*/ * ui_destroy_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  UI_FLAG_DUPL_DATA ; 
 int /*<<< orphan*/  UI_F_UI_DUP_USER_DATA ; 
 int /*<<< orphan*/  UI_R_USER_DATA_DUPLICATION_UNSUPPORTED ; 
 int /*<<< orphan*/  UI_add_user_data (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* stub1 (TYPE_2__*,void*) ; 

int UI_dup_user_data(UI *ui, void *user_data)
{
    void *duplicate = NULL;

    if (ui->meth->ui_duplicate_data == NULL
        || ui->meth->ui_destroy_data == NULL) {
        UIerr(UI_F_UI_DUP_USER_DATA, UI_R_USER_DATA_DUPLICATION_UNSUPPORTED);
        return -1;
    }

    duplicate = ui->meth->ui_duplicate_data(ui, user_data);
    if (duplicate == NULL) {
        UIerr(UI_F_UI_DUP_USER_DATA, ERR_R_MALLOC_FAILURE);
        return -1;
    }

    (void)UI_add_user_data(ui, duplicate);
    ui->flags |= UI_FLAG_DUPL_DATA;

    return 0;
}