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
typedef  int /*<<< orphan*/  UI_METHOD ;
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_UI_LIB ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  OSSL_STORE_F_FILE_GET_PASS ; 
 int /*<<< orphan*/  OSSL_STORE_R_UI_PROCESS_INTERRUPTED_OR_CANCELLED ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_INPUT_FLAG_DEFAULT_PWD ; 
 int /*<<< orphan*/  UI_add_input_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  UI_add_user_data (int /*<<< orphan*/ *,void*) ; 
 char* UI_construct_prompt (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  UI_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UI_new () ; 
 int UI_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_set_method (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static char *file_get_pass(const UI_METHOD *ui_method, char *pass,
                           size_t maxsize, const char *prompt_info, void *data)
{
    UI *ui = UI_new();
    char *prompt = NULL;

    if (ui == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_FILE_GET_PASS, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (ui_method != NULL)
        UI_set_method(ui, ui_method);
    UI_add_user_data(ui, data);

    if ((prompt = UI_construct_prompt(ui, "pass phrase",
                                      prompt_info)) == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_FILE_GET_PASS, ERR_R_MALLOC_FAILURE);
        pass = NULL;
    } else if (!UI_add_input_string(ui, prompt, UI_INPUT_FLAG_DEFAULT_PWD,
                                    pass, 0, maxsize - 1)) {
        OSSL_STOREerr(OSSL_STORE_F_FILE_GET_PASS, ERR_R_UI_LIB);
        pass = NULL;
    } else {
        switch (UI_process(ui)) {
        case -2:
            OSSL_STOREerr(OSSL_STORE_F_FILE_GET_PASS,
                          OSSL_STORE_R_UI_PROCESS_INTERRUPTED_OR_CANCELLED);
            pass = NULL;
            break;
        case -1:
            OSSL_STOREerr(OSSL_STORE_F_FILE_GET_PASS, ERR_R_UI_LIB);
            pass = NULL;
            break;
        default:
            break;
        }
    }

    OPENSSL_free(prompt);
    UI_free(ui);
    return pass;
}