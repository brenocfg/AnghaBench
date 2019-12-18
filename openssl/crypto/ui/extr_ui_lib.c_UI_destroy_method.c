#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* name; int /*<<< orphan*/  ex_data; } ;
typedef  TYPE_1__ UI_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_UI_METHOD ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void UI_destroy_method(UI_METHOD *ui_method)
{
    if (ui_method == NULL)
        return;
    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_UI_METHOD, ui_method,
                        &ui_method->ex_data);
    OPENSSL_free(ui_method->name);
    ui_method->name = NULL;
    OPENSSL_free(ui_method);
}