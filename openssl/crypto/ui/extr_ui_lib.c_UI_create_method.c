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
struct TYPE_7__ {struct TYPE_7__* name; int /*<<< orphan*/  ex_data; } ;
typedef  TYPE_1__ UI_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_UI_METHOD ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  UI_F_UI_CREATE_METHOD ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UI_METHOD *UI_create_method(const char *name)
{
    UI_METHOD *ui_method = NULL;

    if ((ui_method = OPENSSL_zalloc(sizeof(*ui_method))) == NULL
        || (ui_method->name = OPENSSL_strdup(name)) == NULL
        || !CRYPTO_new_ex_data(CRYPTO_EX_INDEX_UI_METHOD, ui_method,
                               &ui_method->ex_data)) {
        if (ui_method)
            OPENSSL_free(ui_method->name);
        OPENSSL_free(ui_method);
        UIerr(UI_F_UI_CREATE_METHOD, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    return ui_method;
}