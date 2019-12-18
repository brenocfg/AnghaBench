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
struct option {struct callchain_param* value; } ;
struct callchain_param {int enabled; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int use_callchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_NONE ; 
 int parse_callchain_report_opt (char const*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int
report_parse_callchain_opt(const struct option *opt, const char *arg, int unset)
{
	struct callchain_param *callchain = opt->value;

	callchain->enabled = !unset;
	/*
	 * --no-call-graph
	 */
	if (unset) {
		symbol_conf.use_callchain = false;
		callchain->mode = CHAIN_NONE;
		return 0;
	}

	return parse_callchain_report_opt(arg);
}