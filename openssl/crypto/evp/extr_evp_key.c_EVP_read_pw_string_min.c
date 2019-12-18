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
 int BUFSIZ ; 
 int /*<<< orphan*/  OPENSSL_cleanse (char*,int) ; 
 scalar_t__ UI_add_input_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ UI_add_verify_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int /*<<< orphan*/  UI_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UI_new () ; 
 int UI_process (int /*<<< orphan*/ *) ; 
 char* prompt_string ; 

int EVP_read_pw_string_min(char *buf, int min, int len, const char *prompt,
                           int verify)
{
    int ret = -1;
    char buff[BUFSIZ];
    UI *ui;

    if ((prompt == NULL) && (prompt_string[0] != '\0'))
        prompt = prompt_string;
    ui = UI_new();
    if (ui == NULL)
        return ret;
    if (UI_add_input_string(ui, prompt, 0, buf, min,
                            (len >= BUFSIZ) ? BUFSIZ - 1 : len) < 0
        || (verify
            && UI_add_verify_string(ui, prompt, 0, buff, min,
                                    (len >= BUFSIZ) ? BUFSIZ - 1 : len,
                                    buf) < 0))
        goto end;
    ret = UI_process(ui);
    OPENSSL_cleanse(buff, BUFSIZ);
 end:
    UI_free(ui);
    return ret;
}