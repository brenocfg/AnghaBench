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
struct parse_opt_ctx_t {int argc; char** argv; } ;
struct option {char const short_name; scalar_t__ long_name; scalar_t__ help; } ;

/* Variables and functions */
 int /*<<< orphan*/ * strcasestr (scalar_t__,char const*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static bool option__in_argv(const struct option *opt, const struct parse_opt_ctx_t *ctx)
{
	int i;

	for (i = 1; i < ctx->argc; ++i) {
		const char *arg = ctx->argv[i];

		if (arg[0] != '-') {
			if (arg[1] == '\0') {
				if (arg[0] == opt->short_name)
					return true;
				continue;
			}

			if (opt->long_name && strcmp(opt->long_name, arg) == 0)
				return true;

			if (opt->help && strcasestr(opt->help, arg) != NULL)
				return true;

			continue;
		}

		if (arg[1] == opt->short_name ||
		    (arg[1] == '-' && opt->long_name && strcmp(opt->long_name, arg + 2) == 0))
			return true;
	}

	return false;
}