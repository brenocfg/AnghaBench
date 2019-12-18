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
typedef  int /*<<< orphan*/  CGI_varlist ;
typedef  scalar_t__ CGI_value ;

/* Variables and functions */
 char* CGI_first_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CGI_free_varlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CGI_get_all (char*) ; 
 scalar_t__* CGI_lookup_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* CGI_next_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 

int
main(int argc, char **argv, char **env) {
    CGI_varlist *vl;
    const char *name;
    CGI_value  *value;
    int i;

    fputs("Content-type: text/plain\r\n\r\n", stdout);
    fputs("Environment:\r\n", stdout);
    for (i = 0; env[i] != 0; i++) {
        fputs(env[i], stdout);
        fputs("\r\n", stdout);
    }

    if ((vl = CGI_get_all("/tmp/cgi-upload-XXXXXX")) == 0) {
        fputs("CGI_get_all() failed\r\n", stdout);
        return 0;
    }
    fputs("\r\nCGI Variables:\r\n", stdout);

    for (name = CGI_first_name(vl); name != 0;
        name = CGI_next_name(vl))
    {
        value = CGI_lookup_all(vl, 0);
        for (i = 0; value[i] != 0; i++) {
            printf("%s [%d] >>%s<<\r\n", name, i, value[i]);
        }
    }
    CGI_free_varlist(vl);
    return 0;
}