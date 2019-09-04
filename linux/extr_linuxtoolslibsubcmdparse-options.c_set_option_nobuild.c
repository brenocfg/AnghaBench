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
struct option {char const* build_opt; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_OPT_CANSKIP ; 
 int /*<<< orphan*/  PARSE_OPT_NOBUILD ; 
 struct option* find_option (struct option*,int,char const*) ; 

void set_option_nobuild(struct option *opts, int shortopt,
			const char *longopt,
			const char *build_opt,
			bool can_skip)
{
	struct option *opt = find_option(opts, shortopt, longopt);

	if (!opt)
		return;

	opt->flags |= PARSE_OPT_NOBUILD;
	opt->flags |= can_skip ? PARSE_OPT_CANSKIP : 0;
	opt->build_opt = build_opt;
}