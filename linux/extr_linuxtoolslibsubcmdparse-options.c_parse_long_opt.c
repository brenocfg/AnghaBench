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
struct parse_opt_ctx_t {char const** out; char const* opt; int /*<<< orphan*/  cpidx; } ;
struct option {scalar_t__ type; char* long_name; struct option* parent; } ;

/* Variables and functions */
 scalar_t__ OPTION_ARGUMENT ; 
 scalar_t__ OPTION_END ; 
 int OPT_UNSET ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,char*,char*,char*) ; 
 int get_value (struct parse_opt_ctx_t*,struct option const*,int) ; 
 int opterror (struct option const*,char*,int) ; 
 char* skip_prefix (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 scalar_t__ strstarts (char*,char const*) ; 

__attribute__((used)) static int parse_long_opt(struct parse_opt_ctx_t *p, const char *arg,
                          const struct option *options)
{
	const char *arg_end = strchr(arg, '=');
	const struct option *abbrev_option = NULL, *ambiguous_option = NULL;
	int abbrev_flags = 0, ambiguous_flags = 0;

	if (!arg_end)
		arg_end = arg + strlen(arg);

retry:
	for (; options->type != OPTION_END; options++) {
		const char *rest;
		int flags = 0;

		if (!options->long_name)
			continue;

		rest = skip_prefix(arg, options->long_name);
		if (options->type == OPTION_ARGUMENT) {
			if (!rest)
				continue;
			if (*rest == '=')
				return opterror(options, "takes no value", flags);
			if (*rest)
				continue;
			p->out[p->cpidx++] = arg - 2;
			return 0;
		}
		if (!rest) {
			if (strstarts(options->long_name, "no-")) {
				/*
				 * The long name itself starts with "no-", so
				 * accept the option without "no-" so that users
				 * do not have to enter "no-no-" to get the
				 * negation.
				 */
				rest = skip_prefix(arg, options->long_name + 3);
				if (rest) {
					flags |= OPT_UNSET;
					goto match;
				}
				/* Abbreviated case */
				if (strstarts(options->long_name + 3, arg)) {
					flags |= OPT_UNSET;
					goto is_abbreviated;
				}
			}
			/* abbreviated? */
			if (!strncmp(options->long_name, arg, arg_end - arg)) {
is_abbreviated:
				if (abbrev_option) {
					/*
					 * If this is abbreviated, it is
					 * ambiguous. So when there is no
					 * exact match later, we need to
					 * error out.
					 */
					ambiguous_option = abbrev_option;
					ambiguous_flags = abbrev_flags;
				}
				if (!(flags & OPT_UNSET) && *arg_end)
					p->opt = arg_end + 1;
				abbrev_option = options;
				abbrev_flags = flags;
				continue;
			}
			/* negated and abbreviated very much? */
			if (strstarts("no-", arg)) {
				flags |= OPT_UNSET;
				goto is_abbreviated;
			}
			/* negated? */
			if (strncmp(arg, "no-", 3))
				continue;
			flags |= OPT_UNSET;
			rest = skip_prefix(arg + 3, options->long_name);
			/* abbreviated and negated? */
			if (!rest && strstarts(options->long_name, arg + 3))
				goto is_abbreviated;
			if (!rest)
				continue;
		}
match:
		if (*rest) {
			if (*rest != '=')
				continue;
			p->opt = rest + 1;
		}
		return get_value(p, options, flags);
	}

	if (ambiguous_option) {
		 fprintf(stderr,
			 " Error: Ambiguous option: %s (could be --%s%s or --%s%s)\n",
			 arg,
			 (ambiguous_flags & OPT_UNSET) ?  "no-" : "",
			 ambiguous_option->long_name,
			 (abbrev_flags & OPT_UNSET) ?  "no-" : "",
			 abbrev_option->long_name);
		 return -1;
	}
	if (abbrev_option)
		return get_value(p, abbrev_option, abbrev_flags);

	if (options->parent) {
		options = options->parent;
		goto retry;
	}

	return -2;
}