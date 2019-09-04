#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parse_opt_ctx_t {char** argv; int /*<<< orphan*/ * opt; } ;
struct option {char const* const long_name; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  exec_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTION_END ; 
#define  PARSE_OPT_DONE 131 
#define  PARSE_OPT_HELP 130 
#define  PARSE_OPT_LIST_OPTS 129 
#define  PARSE_OPT_LIST_SUBCMDS 128 
 int /*<<< orphan*/  astrcat (char**,char const* const) ; 
 int /*<<< orphan*/  astrcatf (char**,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  error_buf ; 
 int /*<<< orphan*/  exit (int) ; 
 int parse_options_end (struct parse_opt_ctx_t*) ; 
 int /*<<< orphan*/  parse_options_start (struct parse_opt_ctx_t*,int,char const**,int) ; 
 int parse_options_step (struct parse_opt_ctx_t*,struct option const*,char const**) ; 
 int /*<<< orphan*/  printf (char*,char const* const) ; 
 int /*<<< orphan*/  putchar (char) ; 
 TYPE_1__ subcmd_config ; 
 int /*<<< orphan*/  usage_with_options (char const**,struct option const*) ; 

int parse_options_subcommand(int argc, const char **argv, const struct option *options,
			const char *const subcommands[], const char *usagestr[], int flags)
{
	struct parse_opt_ctx_t ctx;

	/* build usage string if it's not provided */
	if (subcommands && !usagestr[0]) {
		char *buf = NULL;

		astrcatf(&buf, "%s %s [<options>] {", subcmd_config.exec_name, argv[0]);

		for (int i = 0; subcommands[i]; i++) {
			if (i)
				astrcat(&buf, "|");
			astrcat(&buf, subcommands[i]);
		}
		astrcat(&buf, "}");

		usagestr[0] = buf;
	}

	parse_options_start(&ctx, argc, argv, flags);
	switch (parse_options_step(&ctx, options, usagestr)) {
	case PARSE_OPT_HELP:
		exit(129);
	case PARSE_OPT_DONE:
		break;
	case PARSE_OPT_LIST_OPTS:
		while (options->type != OPTION_END) {
			if (options->long_name)
				printf("--%s ", options->long_name);
			options++;
		}
		putchar('\n');
		exit(130);
	case PARSE_OPT_LIST_SUBCMDS:
		if (subcommands) {
			for (int i = 0; subcommands[i]; i++)
				printf("%s ", subcommands[i]);
		}
		putchar('\n');
		exit(130);
	default: /* PARSE_OPT_UNKNOWN */
		if (ctx.argv[0][1] == '-')
			astrcatf(&error_buf, "unknown option `%s'",
				 ctx.argv[0] + 2);
		else
			astrcatf(&error_buf, "unknown switch `%c'", *ctx.opt);
		usage_with_options(usagestr, options);
	}

	return parse_options_end(&ctx);
}