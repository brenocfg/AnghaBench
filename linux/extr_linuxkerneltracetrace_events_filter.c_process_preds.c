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
struct trace_event_call {int dummy; } ;
struct prog_entry {int dummy; } ;
struct filter_parse_error {int dummy; } ;
struct event_filter {int /*<<< orphan*/  prog; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FILT_ERR_MISSING_QUOTE ; 
 int /*<<< orphan*/  FILT_ERR_TOO_MANY_CLOSE ; 
 int /*<<< orphan*/  FILT_ERR_TOO_MANY_OPEN ; 
 scalar_t__ IS_ERR (struct prog_entry*) ; 
#define  MISSING_QUOTE 129 
 int PTR_ERR (struct prog_entry*) ; 
#define  TOO_MANY_OPEN 128 
 int calc_stack (char const*,int*,int*,int*) ; 
 int /*<<< orphan*/  parse_error (struct filter_parse_error*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_pred ; 
 struct prog_entry* predicate_parse (char const*,int,int,int /*<<< orphan*/ ,struct trace_event_call*,struct filter_parse_error*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct prog_entry*) ; 

__attribute__((used)) static int process_preds(struct trace_event_call *call,
			 const char *filter_string,
			 struct event_filter *filter,
			 struct filter_parse_error *pe)
{
	struct prog_entry *prog;
	int nr_parens;
	int nr_preds;
	int index;
	int ret;

	ret = calc_stack(filter_string, &nr_parens, &nr_preds, &index);
	if (ret < 0) {
		switch (ret) {
		case MISSING_QUOTE:
			parse_error(pe, FILT_ERR_MISSING_QUOTE, index);
			break;
		case TOO_MANY_OPEN:
			parse_error(pe, FILT_ERR_TOO_MANY_OPEN, index);
			break;
		default:
			parse_error(pe, FILT_ERR_TOO_MANY_CLOSE, index);
		}
		return ret;
	}

	if (!nr_preds)
		return -EINVAL;

	prog = predicate_parse(filter_string, nr_parens, nr_preds,
			       parse_pred, call, pe);
	if (IS_ERR(prog))
		return PTR_ERR(prog);

	rcu_assign_pointer(filter->prog, prog);
	return 0;
}