#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct parse_state {char** member_1; int /*<<< orphan*/  arg; int /*<<< orphan*/  param; scalar_t__ is_opt; TYPE_2__* member_0; } ;
struct mpv_global {int dummy; } ;
struct TYPE_6__ {int num_opts; TYPE_1__* opts; } ;
typedef  TYPE_2__ m_config_t ;
struct TYPE_5__ {int warning_was_printed; } ;

/* Variables and functions */
 int M_SETOPT_FROM_CMDLINE ; 
 int M_SETOPT_PRE_PARSE_ONLY ; 
 scalar_t__ bstrcmp0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_config_set_option_cli (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ split_opt_silent (struct parse_state*) ; 

void m_config_preparse_command_line(m_config_t *config, struct mpv_global *global,
                                    int *verbose, char **argv)
{
    struct parse_state p = {config, argv};
    while (split_opt_silent(&p) == 0) {
        if (p.is_opt) {
            // Ignore non-pre-parse options. They will be set later.
            // Option parsing errors will be handled later as well.
            int flags = M_SETOPT_FROM_CMDLINE | M_SETOPT_PRE_PARSE_ONLY;
            m_config_set_option_cli(config, p.arg, p.param, flags);
            if (bstrcmp0(p.arg, "v") == 0)
                (*verbose)++;
        }
    }

    for (int n = 0; n < config->num_opts; n++)
        config->opts[n].warning_was_printed = false;
}