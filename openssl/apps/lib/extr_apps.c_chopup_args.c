#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t argc; int size; char** argv; } ;
typedef  TYPE_1__ ARGS ;

/* Variables and functions */
 char** OPENSSL_realloc (char**,int) ; 
 int /*<<< orphan*/  _UC (char) ; 
 char** app_malloc (int,char*) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 

int chopup_args(ARGS *arg, char *buf)
{
    int quoted;
    char c = '\0', *p = NULL;

    arg->argc = 0;
    if (arg->size == 0) {
        arg->size = 20;
        arg->argv = app_malloc(sizeof(*arg->argv) * arg->size, "argv space");
    }

    for (p = buf;;) {
        /* Skip whitespace. */
        while (*p && isspace(_UC(*p)))
            p++;
        if (*p == '\0')
            break;

        /* The start of something good :-) */
        if (arg->argc >= arg->size) {
            char **tmp;
            arg->size += 20;
            tmp = OPENSSL_realloc(arg->argv, sizeof(*arg->argv) * arg->size);
            if (tmp == NULL)
                return 0;
            arg->argv = tmp;
        }
        quoted = *p == '\'' || *p == '"';
        if (quoted)
            c = *p++;
        arg->argv[arg->argc++] = p;

        /* now look for the end of this */
        if (quoted) {
            while (*p && *p != c)
                p++;
            *p++ = '\0';
        } else {
            while (*p && !isspace(_UC(*p)))
                p++;
            if (*p)
                *p++ = '\0';
        }
    }
    arg->argv[arg->argc] = NULL;
    return 1;
}