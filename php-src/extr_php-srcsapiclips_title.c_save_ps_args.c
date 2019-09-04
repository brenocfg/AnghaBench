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
 int save_argc ; 
 char** save_argv ; 

char** save_ps_args(int argc, char** argv)
{
    save_argc = argc;
    save_argv = argv;

#if defined(PS_USE_CLOBBER_ARGV)
    /*
     * If we're going to overwrite the argv area, count the available space.
     * Also move the environment to make additional room.
     */
    {
        char* end_of_area = NULL;
        int non_contiguous_area = 0;
        int i;

        /*
         * check for contiguous argv strings
         */
        for (i = 0; (non_contiguous_area == 0) && (i < argc); i++)
        {
            if (i != 0 && end_of_area + 1 != argv[i])
                non_contiguous_area = 1;
            end_of_area = argv[i] + strlen(argv[i]);
        }

        /*
         * check for contiguous environ strings following argv
         */
        for (i = 0; (non_contiguous_area == 0) && (environ[i] != NULL); i++)
        {
            if (end_of_area + 1 != environ[i])
                non_contiguous_area = 1;
            end_of_area = environ[i] + strlen(environ[i]);
        }

        if (non_contiguous_area != 0)
            goto clobber_error;

        ps_buffer = argv[0];
        ps_buffer_size = end_of_area - argv[0];

        /*
         * move the environment out of the way
         */
        new_environ = (char **) malloc((i + 1) * sizeof(char *));
        frozen_environ = (char **) malloc((i + 1) * sizeof(char *));
        if (!new_environ || !frozen_environ)
            goto clobber_error;
        for (i = 0; environ[i] != NULL; i++)
        {
            new_environ[i] = strdup(environ[i]);
            if (!new_environ[i])
                goto clobber_error;
        }
        new_environ[i] = NULL;
        environ = new_environ;
        memcpy((char *)frozen_environ, (char *)new_environ, sizeof(char *) * (i + 1));

    }
#endif /* PS_USE_CLOBBER_ARGV */

#if defined(PS_USE_CHANGE_ARGV) || defined(PS_USE_CLOBBER_ARGV)
    /*
     * If we're going to change the original argv[] then make a copy for
     * argument parsing purposes.
     *
     * (NB: do NOT think to remove the copying of argv[]!
     * On some platforms, getopt() keeps pointers into the argv array, and
     * will get horribly confused when it is re-called to analyze a subprocess'
     * argument string if the argv storage has been clobbered meanwhile.
     * Other platforms have other dependencies on argv[].)
     */
    {
        char** new_argv;
        int i;

        new_argv = (char **) malloc((argc + 1) * sizeof(char *));
        if (!new_argv)
            goto clobber_error;
        for (i = 0; i < argc; i++)
        {
            new_argv[i] = strdup(argv[i]);
            if (!new_argv[i]) {
                free(new_argv);
                goto clobber_error;
            }
        }
        new_argv[argc] = NULL;

#if defined(DARWIN)
        /*
         * Darwin (and perhaps other NeXT-derived platforms?) has a static
         * copy of the argv pointer, which we may fix like so:
         */
        *_NSGetArgv() = new_argv;
#endif

        argv = new_argv;

    }
#endif /* PS_USE_CHANGE_ARGV or PS_USE_CLOBBER_ARGV */

#if defined(PS_USE_CLOBBER_ARGV)
    {
        /* make extra argv slots point at end_of_area (a NUL) */
        int i;
        for (i = 1; i < save_argc; i++)
            save_argv[i] = ps_buffer + ps_buffer_size;
    }
#endif /* PS_USE_CLOBBER_ARGV */

#ifdef PS_USE_CHANGE_ARGV
    save_argv[0] = ps_buffer; /* ps_buffer here is a static const array of size PS_BUFFER_SIZE */
    save_argv[1] = NULL;
#endif /* PS_USE_CHANGE_ARGV */

    return argv;

#if defined(PS_USE_CHANGE_ARGV) || defined(PS_USE_CLOBBER_ARGV)
clobber_error:
    /* probably can't happen?!
     * if we ever get here, argv still points to originally passed
     * in argument
     */
    save_argv = NULL;
    save_argc = 0;
    ps_buffer = NULL;
    ps_buffer_size = 0;
    return argv;
#endif /* PS_USE_CHANGE_ARGV or PS_USE_CLOBBER_ARGV */
}