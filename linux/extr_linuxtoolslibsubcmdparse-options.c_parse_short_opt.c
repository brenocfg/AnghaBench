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
struct parse_opt_ctx_t {scalar_t__* opt; } ;
struct option {scalar_t__ type; scalar_t__ short_name; struct option* parent; } ;

/* Variables and functions */
 scalar_t__ OPTION_END ; 
 int /*<<< orphan*/  OPT_SHORT ; 
 int get_value (struct parse_opt_ctx_t*,struct option const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_short_opt(struct parse_opt_ctx_t *p, const struct option *options)
{
retry:
	for (; options->type != OPTION_END; options++) {
		if (options->short_name == *p->opt) {
			p->opt = p->opt[1] ? p->opt + 1 : NULL;
			return get_value(p, options, OPT_SHORT);
		}
	}

	if (options->parent) {
		options = options->parent;
		goto retry;
	}

	return -2;
}