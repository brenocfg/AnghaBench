#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dirent {int /*<<< orphan*/  d_name; } ;
struct TYPE_6__ {int expect_file_generations; char const* entry_name; int /*<<< orphan*/  previous_entry_name; int /*<<< orphan*/ * dir; } ;
typedef  TYPE_1__ LP_DIR_CTX ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char const*,int /*<<< orphan*/ ,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ isdigit (char) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

const char *LP_find_file(LP_DIR_CTX **ctx, const char *directory)
{
    struct dirent *direntry = NULL;

    if (ctx == NULL || directory == NULL) {
        errno = EINVAL;
        return 0;
    }

    errno = 0;
    if (*ctx == NULL) {
        *ctx = malloc(sizeof(**ctx));
        if (*ctx == NULL) {
            errno = ENOMEM;
            return 0;
        }
        memset(*ctx, 0, sizeof(**ctx));

#ifdef __VMS
        {
            char c = directory[strlen(directory) - 1];

            if (c == ']' || c == '>' || c == ':')
                (*ctx)->expect_file_generations = 1;
        }
#endif

        (*ctx)->dir = opendir(directory);
        if ((*ctx)->dir == NULL) {
            int save_errno = errno; /* Probably not needed, but I'm paranoid */
            free(*ctx);
            *ctx = NULL;
            errno = save_errno;
            return 0;
        }
    }

#ifdef __VMS
    strncpy((*ctx)->previous_entry_name, (*ctx)->entry_name,
            sizeof((*ctx)->previous_entry_name));

 again:
#endif

    direntry = readdir((*ctx)->dir);
    if (direntry == NULL) {
        return 0;
    }

    OPENSSL_strlcpy((*ctx)->entry_name, direntry->d_name,
                    sizeof((*ctx)->entry_name));
#ifdef __VMS
    if ((*ctx)->expect_file_generations) {
        char *p = (*ctx)->entry_name + strlen((*ctx)->entry_name);

        while(p > (*ctx)->entry_name && isdigit(p[-1]))
            p--;
        if (p > (*ctx)->entry_name && p[-1] == ';')
            p[-1] = '\0';
        if (strcasecmp((*ctx)->entry_name, (*ctx)->previous_entry_name) == 0)
            goto again;
    }
#endif
    return (*ctx)->entry_name;
}