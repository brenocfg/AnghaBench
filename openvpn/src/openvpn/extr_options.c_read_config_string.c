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
typedef  int /*<<< orphan*/  uint8_t ;
struct options {int /*<<< orphan*/  gc; } ;
struct env_set {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (char**) ; 
 int /*<<< orphan*/  MAX_PARMS ; 
 int OPTION_LINE_SIZE ; 
 scalar_t__ SIZE (char**) ; 
 int /*<<< orphan*/  add_option (struct options*,char**,char const*,int,int /*<<< orphan*/ ,int const,unsigned int const,unsigned int*,struct env_set*) ; 
 scalar_t__ buf_parse (struct buffer*,char,char*,int) ; 
 int /*<<< orphan*/  buf_set_read (struct buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bypass_doubledash (char**) ; 
 int /*<<< orphan*/  check_inline_file_via_buf (struct buffer*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_line (char*,char**,scalar_t__,char const*,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secure_memzero (char*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
read_config_string(const char *prefix,
                   struct options *options,
                   const char *config,
                   const int msglevel,
                   const unsigned int permission_mask,
                   unsigned int *option_types_found,
                   struct env_set *es)
{
    char line[OPTION_LINE_SIZE];
    struct buffer multiline;
    int line_num = 0;

    buf_set_read(&multiline, (uint8_t *)config, strlen(config));

    while (buf_parse(&multiline, '\n', line, sizeof(line)))
    {
        char *p[MAX_PARMS+1];
        CLEAR(p);
        ++line_num;
        if (parse_line(line, p, SIZE(p)-1, prefix, line_num, msglevel, &options->gc))
        {
            bypass_doubledash(&p[0]);
            check_inline_file_via_buf(&multiline, p, &options->gc);
            add_option(options, p, prefix, line_num, 0, msglevel, permission_mask, option_types_found, es);
        }
        CLEAR(p);
    }
    secure_memzero(line, sizeof(line));
}