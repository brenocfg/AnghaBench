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
struct record_opts {int auxtrace_snapshot_on_exit; } ;
struct auxtrace_record {int (* parse_snapshot_options ) (struct auxtrace_record*,struct record_opts*,char const*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct auxtrace_record*,struct record_opts*,char const*) ; 

int auxtrace_parse_snapshot_options(struct auxtrace_record *itr,
				    struct record_opts *opts, const char *str)
{
	if (!str)
		return 0;

	/* PMU-agnostic options */
	switch (*str) {
	case 'e':
		opts->auxtrace_snapshot_on_exit = true;
		str++;
		break;
	default:
		break;
	}

	if (itr)
		return itr->parse_snapshot_options(itr, opts, str);

	pr_err("No AUX area tracing to snapshot\n");
	return -EINVAL;
}