#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  strings; int /*<<< orphan*/  user_data; TYPE_1__* meth; } ;
typedef  TYPE_2__ UI ;
struct TYPE_7__ {int /*<<< orphan*/  (* ui_destroy_data ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_UI ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int UI_FLAG_DUPL_DATA ; 
 int /*<<< orphan*/  free_string ; 
 int /*<<< orphan*/  sk_UI_STRING_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void UI_free(UI *ui)
{
    if (ui == NULL)
        return;
    if ((ui->flags & UI_FLAG_DUPL_DATA) != 0) {
        ui->meth->ui_destroy_data(ui, ui->user_data);
    }
    sk_UI_STRING_pop_free(ui->strings, free_string);
    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_UI, ui, &ui->ex_data);
    CRYPTO_THREAD_lock_free(ui->lock);
    OPENSSL_free(ui);
}