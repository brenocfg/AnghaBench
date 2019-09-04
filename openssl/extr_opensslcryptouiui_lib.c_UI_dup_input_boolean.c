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
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  UIT_BOOLEAN ; 
 int /*<<< orphan*/  UI_F_UI_DUP_INPUT_BOOLEAN ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int general_allocate_boolean (int /*<<< orphan*/ *,char*,char*,char*,char*,int,int /*<<< orphan*/ ,int,char*) ; 

int UI_dup_input_boolean(UI *ui, const char *prompt, const char *action_desc,
                         const char *ok_chars, const char *cancel_chars,
                         int flags, char *result_buf)
{
    char *prompt_copy = NULL;
    char *action_desc_copy = NULL;
    char *ok_chars_copy = NULL;
    char *cancel_chars_copy = NULL;

    if (prompt != NULL) {
        prompt_copy = OPENSSL_strdup(prompt);
        if (prompt_copy == NULL) {
            UIerr(UI_F_UI_DUP_INPUT_BOOLEAN, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }

    if (action_desc != NULL) {
        action_desc_copy = OPENSSL_strdup(action_desc);
        if (action_desc_copy == NULL) {
            UIerr(UI_F_UI_DUP_INPUT_BOOLEAN, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }

    if (ok_chars != NULL) {
        ok_chars_copy = OPENSSL_strdup(ok_chars);
        if (ok_chars_copy == NULL) {
            UIerr(UI_F_UI_DUP_INPUT_BOOLEAN, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }

    if (cancel_chars != NULL) {
        cancel_chars_copy = OPENSSL_strdup(cancel_chars);
        if (cancel_chars_copy == NULL) {
            UIerr(UI_F_UI_DUP_INPUT_BOOLEAN, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }

    return general_allocate_boolean(ui, prompt_copy, action_desc_copy,
                                    ok_chars_copy, cancel_chars_copy, 1,
                                    UIT_BOOLEAN, flags, result_buf);
 err:
    OPENSSL_free(prompt_copy);
    OPENSSL_free(action_desc_copy);
    OPENSSL_free(ok_chars_copy);
    OPENSSL_free(cancel_chars_copy);
    return -1;
}