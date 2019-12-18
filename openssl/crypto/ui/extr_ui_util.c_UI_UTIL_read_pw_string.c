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

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  OPENSSL_cleanse (char*,int) ; 
 int UI_UTIL_read_pw (char*,char*,int,char const*,int) ; 

int UI_UTIL_read_pw_string(char *buf, int length, const char *prompt,
                           int verify)
{
    char buff[BUFSIZ];
    int ret;

    ret =
        UI_UTIL_read_pw(buf, buff, (length > BUFSIZ) ? BUFSIZ : length,
                        prompt, verify);
    OPENSSL_cleanse(buff, BUFSIZ);
    return ret;
}