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
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  UIT_VERIFY ; 
 int /*<<< orphan*/  UI_F_UI_DUP_VERIFY_STRING ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int general_allocate_string (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,char*,int,int,char const*) ; 

int UI_dup_verify_string(UI *ui, const char *prompt, int flags,
                         char *result_buf, int minsize, int maxsize,
                         const char *test_buf)
{
    char *prompt_copy = NULL;

    if (prompt != NULL) {
        prompt_copy = OPENSSL_strdup(prompt);
        if (prompt_copy == NULL) {
            UIerr(UI_F_UI_DUP_VERIFY_STRING, ERR_R_MALLOC_FAILURE);
            return -1;
        }
    }

    return general_allocate_string(ui, prompt_copy, 1,
                                   UIT_VERIFY, flags, result_buf, minsize,
                                   maxsize, test_buf);
}