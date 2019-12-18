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
struct options {int /*<<< orphan*/  gc; } ;
struct env_set {int dummy; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (char**) ; 
 int /*<<< orphan*/  MAX_PARMS ; 
 int OPTION_LINE_SIZE ; 
 scalar_t__ SIZE (char**) ; 
 int /*<<< orphan*/  add_option (struct options*,char**,char const*,int,int,int const,unsigned int const,unsigned int*,struct env_set*) ; 
 int /*<<< orphan*/  bypass_doubledash (char**) ; 
 int /*<<< orphan*/  check_inline_file_via_fp (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int const,char*,char const*,int const,...) ; 
 scalar_t__ parse_line (char*,char**,scalar_t__,char const*,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * platform_fopen (char const*,char*) ; 
 int /*<<< orphan*/  secure_memzero (char*,int) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ streq (char const*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
read_config_file(struct options *options,
                 const char *file,
                 int level,
                 const char *top_file,
                 const int top_line,
                 const int msglevel,
                 const unsigned int permission_mask,
                 unsigned int *option_types_found,
                 struct env_set *es)
{
    const int max_recursive_levels = 10;
    FILE *fp;
    int line_num;
    char line[OPTION_LINE_SIZE+1];
    char *p[MAX_PARMS+1];

    ++level;
    if (level <= max_recursive_levels)
    {
        if (streq(file, "stdin"))
        {
            fp = stdin;
        }
        else
        {
            fp = platform_fopen(file, "r");
        }
        if (fp)
        {
            line_num = 0;
            while (fgets(line, sizeof(line), fp))
            {
                int offset = 0;
                CLEAR(p);
                ++line_num;
                if (strlen(line) == OPTION_LINE_SIZE)
                {
                    msg(msglevel, "In %s:%d: Maximum option line length (%d) exceeded, line starts with %s",
                        file, line_num, OPTION_LINE_SIZE, line);
                }

                /* Ignore UTF-8 BOM at start of stream */
                if (line_num == 1 && strncmp(line, "\xEF\xBB\xBF", 3) == 0)
                {
                    offset = 3;
                }
                if (parse_line(line + offset, p, SIZE(p)-1, file, line_num, msglevel, &options->gc))
                {
                    bypass_doubledash(&p[0]);
                    check_inline_file_via_fp(fp, p, &options->gc);
                    add_option(options, p, file, line_num, level, msglevel, permission_mask, option_types_found, es);
                }
            }
            if (fp != stdin)
            {
                fclose(fp);
            }
        }
        else
        {
            msg(msglevel, "In %s:%d: Error opening configuration file: %s", top_file, top_line, file);
        }
    }
    else
    {
        msg(msglevel, "In %s:%d: Maximum recursive include levels exceeded in include attempt of file %s -- probably you have a configuration file that tries to include itself.", top_file, top_line, file);
    }
    secure_memzero(line, sizeof(line));
    CLEAR(p);
}