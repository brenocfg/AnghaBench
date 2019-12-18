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
 int /*<<< orphan*/ * CGI_decode_query (int /*<<< orphan*/ *,char*) ; 
 int atoi (char const*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ mymalloc (int) ; 
 int /*<<< orphan*/ * read_multipart (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

CGI_varlist *
CGI_get_post(CGI_varlist *v, const char *template) {
    const char *env;
    char *buf;
    int len;

    if ((env = getenv("CONTENT_TYPE")) != 0 &&
        strncasecmp(env, "application/x-www-form-urlencoded", 33) == 0 &&
        (env = getenv("CONTENT_LENGTH")) != 0 &&
        (len = atoi(env)) > 0)
    {
        buf = (char *) mymalloc(len + 1);
        if (fread(buf, 1, len, stdin) == len) {
            buf[len] = 0;
            v = CGI_decode_query(v, buf);
        }
        free(buf);
    }
    else {
        v = read_multipart(v, template);
    }
    return v;
}