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
 int /*<<< orphan*/  UIT_INFO ; 
 int /*<<< orphan*/  UI_F_UI_DUP_INFO_STRING ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int general_allocate_string (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int UI_dup_info_string(UI *ui, const char *text)
{
    char *text_copy = NULL;

    if (text != NULL) {
        text_copy = OPENSSL_strdup(text);
        if (text_copy == NULL) {
            UIerr(UI_F_UI_DUP_INFO_STRING, ERR_R_MALLOC_FAILURE);
            return -1;
        }
    }

    return general_allocate_string(ui, text_copy, 1, UIT_INFO, 0, NULL,
                                   0, 0, NULL);
}