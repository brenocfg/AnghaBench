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
struct options {int dummy; } ;
struct env_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (char**) ; 
 int MAX_PARMS ; 
 int /*<<< orphan*/  add_option (struct options*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,unsigned int const,unsigned int*,struct env_set*) ; 
 int /*<<< orphan*/  msg (int const,char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  usage () ; 

void
parse_argv(struct options *options,
           const int argc,
           char *argv[],
           const int msglevel,
           const unsigned int permission_mask,
           unsigned int *option_types_found,
           struct env_set *es)
{
    int i, j;

    /* usage message */
    if (argc <= 1)
    {
        usage();
    }

    /* config filename specified only? */
    if (argc == 2 && strncmp(argv[1], "--", 2))
    {
        char *p[MAX_PARMS];
        CLEAR(p);
        p[0] = "config";
        p[1] = argv[1];
        add_option(options, p, NULL, 0, 0, msglevel, permission_mask, option_types_found, es);
    }
    else
    {
        /* parse command line */
        for (i = 1; i < argc; ++i)
        {
            char *p[MAX_PARMS];
            CLEAR(p);
            p[0] = argv[i];
            if (strncmp(p[0], "--", 2))
            {
                msg(msglevel, "I'm trying to parse \"%s\" as an --option parameter but I don't see a leading '--'", p[0]);
            }
            else
            {
                p[0] += 2;
            }

            for (j = 1; j < MAX_PARMS; ++j)
            {
                if (i + j < argc)
                {
                    char *arg = argv[i + j];
                    if (strncmp(arg, "--", 2))
                    {
                        p[j] = arg;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            add_option(options, p, NULL, 0, 0, msglevel, permission_mask, option_types_found, es);
            i += j - 1;
        }
    }
}