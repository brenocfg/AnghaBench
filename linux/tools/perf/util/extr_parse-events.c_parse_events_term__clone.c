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
struct TYPE_2__ {int /*<<< orphan*/  num; int /*<<< orphan*/  str; } ;
struct parse_events_term {TYPE_1__ val; int /*<<< orphan*/  err_val; int /*<<< orphan*/  err_term; int /*<<< orphan*/  config; int /*<<< orphan*/  type_term; int /*<<< orphan*/  type_val; } ;

/* Variables and functions */
 int new_term (struct parse_events_term**,struct parse_events_term*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int parse_events_term__clone(struct parse_events_term **new,
			     struct parse_events_term *term)
{
	struct parse_events_term temp = {
		.type_val  = term->type_val,
		.type_term = term->type_term,
		.config    = term->config,
		.err_term  = term->err_term,
		.err_val   = term->err_val,
	};

	return new_term(new, &temp, term->val.str, term->val.num);
}