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
 int /*<<< orphan*/  OPENSSL_atexit (int /*<<< orphan*/  (*) ()) ; 
 char** app_malloc (int,char*) ; 
 int /*<<< orphan*/  cleanup_argv () ; 
 char** newargv ; 

char **copy_argv(int *argc, char *argv[])
{
    /*-
     * The note below is for historical purpose.  On VMS now we always
     * copy argv "safely."
     *
     * 2011-03-22 SMS.
     * If we have 32-bit pointers everywhere, then we're safe, and
     * we bypass this mess, as on non-VMS systems.
     * Problem 1: Compaq/HP C before V7.3 always used 32-bit
     * pointers for argv[].
     * Fix 1: For a 32-bit argv[], when we're using 64-bit pointers
     * everywhere else, we always allocate and use a 64-bit
     * duplicate of argv[].
     * Problem 2: Compaq/HP C V7.3 (Alpha, IA64) before ECO1 failed
     * to NULL-terminate a 64-bit argv[].  (As this was written, the
     * compiler ECO was available only on IA64.)
     * Fix 2: Unless advised not to (VMS_TRUST_ARGV), we test a
     * 64-bit argv[argc] for NULL, and, if necessary, use a
     * (properly) NULL-terminated (64-bit) duplicate of argv[].
     * The same code is used in either case to duplicate argv[].
     * Some of these decisions could be handled in preprocessing,
     * but the code tends to get even uglier, and the penalty for
     * deciding at compile- or run-time is tiny.
     */

    int i, count = *argc;
    char **p = newargv;

    cleanup_argv();

    newargv = app_malloc(sizeof(*newargv) * (count + 1), "argv copy");
    if (newargv == NULL)
        return NULL;

    /* Register automatic cleanup on first use */
    if (p == NULL)
        OPENSSL_atexit(cleanup_argv);

    for (i = 0; i < count; i++)
        newargv[i] = argv[i];
    newargv[i] = NULL;
    *argc = i;
    return newargv;
}