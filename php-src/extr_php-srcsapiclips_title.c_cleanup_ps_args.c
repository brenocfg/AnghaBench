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
 scalar_t__ save_argc ; 
 int /*<<< orphan*/ * save_argv ; 

void cleanup_ps_args(char **argv)
{
#ifndef PS_USE_NONE
    if (save_argv)
    {
        save_argv = NULL;
        save_argc = 0;

#ifdef PS_USE_CLOBBER_ARGV
        {
            int i;
            for (i = 0; frozen_environ[i] != NULL; i++)
                free(frozen_environ[i]);
            free(frozen_environ);
            free(new_environ);
            /* leave a sane environment behind since some atexit() handlers
                call getenv(). */
            environ = empty_environ;
        }
#endif /* PS_USE_CLOBBER_ARGV */

#if defined(PS_USE_CHANGE_ARGV) || defined(PS_USE_CLOBBER_ARGV)
        {
            int i;
            for (i=0; argv[i] != NULL; i++)
                free(argv[i]);
            free(argv);
        }
#endif /* PS_USE_CHANGE_ARGV or PS_USE_CLOBBER_ARGV */
    }
#endif /* PS_USE_NONE */

    return;
}