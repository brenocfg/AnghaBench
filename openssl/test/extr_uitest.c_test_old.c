#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pass ;
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_str_eq (char*,char*) ; 
 int /*<<< orphan*/  UI_INPUT_FLAG_DEFAULT_PWD ; 
 int /*<<< orphan*/ * UI_UTIL_wrap_read_pem_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_add_input_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_add_user_data (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UI_destroy_method (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UI_new_method (int /*<<< orphan*/ *) ; 
 int UI_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_pem_password_cb ; 

__attribute__((used)) static int test_old(void)
{
    UI_METHOD *ui_method = NULL;
    UI *ui = NULL;
    char defpass[] = "password";
    char pass[16];
    int ok = 0;

    if (!TEST_ptr(ui_method =
                  UI_UTIL_wrap_read_pem_callback( test_pem_password_cb, 0))
            || !TEST_ptr(ui = UI_new_method(ui_method)))
        goto err;

    /* The wrapper passes the UI userdata as the callback userdata param */
    UI_add_user_data(ui, defpass);

    if (!UI_add_input_string(ui, "prompt", UI_INPUT_FLAG_DEFAULT_PWD,
                             pass, 0, sizeof(pass) - 1))
        goto err;

    switch (UI_process(ui)) {
    case -2:
        TEST_info("test_old: UI process interrupted or cancelled");
        /* fall through */
    case -1:
        goto err;
    default:
        break;
    }

    if (TEST_str_eq(pass, defpass))
        ok = 1;

 err:
    UI_free(ui);
    UI_destroy_method(ui_method);

    return ok;
}