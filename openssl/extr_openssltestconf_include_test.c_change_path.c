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
 int /*<<< orphan*/  DIRSEP ; 
 size_t DIRSEP_PRESERVE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  TEST_note (char*,char*) ; 
 int chdir (char*) ; 
 char* strpbrk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int change_path(const char *file)
{
    char *s = OPENSSL_strdup(file);
    char *p = s;
    char *last = NULL;
    int ret;

    if (s == NULL)
        return -1;

    while ((p = strpbrk(p, DIRSEP)) != NULL) {
        last = p++;
    }
    if (last == NULL)
        return 0;
    last[DIRSEP_PRESERVE] = 0;

    TEST_note("changing path to %s", s);
    ret = chdir(s);
    OPENSSL_free(s);
    return ret;
}