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

/* Variables and functions */
 int /*<<< orphan*/ * CGI_add_var (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ mymalloc (scalar_t__) ; 
 char* scanattr (char*,char**) ; 
 char* strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

CGI_varlist *
CGI_get_cookie(CGI_varlist *v) {
    const char *env;
    char *buf, *p, *cookie[2];

    if ((env = getenv("HTTP_COOKIE")) == 0) {
        return v;
    }
    buf = (char *) mymalloc(strlen(env) + 1);
    p = strcpy(buf, env);
    while ((p = scanattr(p, cookie)) != 0) {
        v = CGI_add_var(v, cookie[0], cookie[1]);
    }
    free(buf);
    return v;
}