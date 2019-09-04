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
 int /*<<< orphan*/  mkdir (char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char const*) ; 

void mp_mkdirp(const char *dir)
{
    char *path = talloc_strdup(NULL, dir);
    char *cdir = path + 1;

    while (cdir) {
        cdir = strchr(cdir, '/');
        if (cdir)
            *cdir = 0;

        mkdir(path, 0700);

        if (cdir)
            *cdir++ = '/';
    }

    talloc_free(path);
}