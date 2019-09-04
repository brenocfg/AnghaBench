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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct perf_event_attr {int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct parse_events_state {int /*<<< orphan*/  idx; int /*<<< orphan*/  error; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int add_event (struct list_head*,int /*<<< orphan*/ *,struct perf_event_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ config_attr (struct perf_event_attr*,struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_term_common ; 
 int /*<<< orphan*/  config_terms ; 
 int /*<<< orphan*/  get_config_name (struct list_head*) ; 
 scalar_t__ get_config_terms (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 

int parse_events_add_numeric(struct parse_events_state *parse_state,
			     struct list_head *list,
			     u32 type, u64 config,
			     struct list_head *head_config)
{
	struct perf_event_attr attr;
	LIST_HEAD(config_terms);

	memset(&attr, 0, sizeof(attr));
	attr.type = type;
	attr.config = config;

	if (head_config) {
		if (config_attr(&attr, head_config, parse_state->error,
				config_term_common))
			return -EINVAL;

		if (get_config_terms(head_config, &config_terms))
			return -ENOMEM;
	}

	return add_event(list, &parse_state->idx, &attr,
			 get_config_name(head_config), &config_terms);
}