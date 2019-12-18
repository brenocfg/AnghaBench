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
struct perf_event_attr {int dummy; } ;
struct parse_events_term {int type_term; int /*<<< orphan*/  err_term; } ;
struct parse_events_error {void* help; void* str; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PARSE_EVENTS__TERM_TYPE_AUX_OUTPUT 136 
#define  PARSE_EVENTS__TERM_TYPE_CALLGRAPH 135 
#define  PARSE_EVENTS__TERM_TYPE_INHERIT 134 
#define  PARSE_EVENTS__TERM_TYPE_MAX_EVENTS 133 
#define  PARSE_EVENTS__TERM_TYPE_MAX_STACK 132 
#define  PARSE_EVENTS__TERM_TYPE_NOINHERIT 131 
#define  PARSE_EVENTS__TERM_TYPE_NOOVERWRITE 130 
#define  PARSE_EVENTS__TERM_TYPE_OVERWRITE 129 
#define  PARSE_EVENTS__TERM_TYPE_STACKSIZE 128 
 int config_term_common (struct perf_event_attr*,struct parse_events_term*,struct parse_events_error*) ; 
 void* strdup (char*) ; 

__attribute__((used)) static int config_term_tracepoint(struct perf_event_attr *attr,
				  struct parse_events_term *term,
				  struct parse_events_error *err)
{
	switch (term->type_term) {
	case PARSE_EVENTS__TERM_TYPE_CALLGRAPH:
	case PARSE_EVENTS__TERM_TYPE_STACKSIZE:
	case PARSE_EVENTS__TERM_TYPE_INHERIT:
	case PARSE_EVENTS__TERM_TYPE_NOINHERIT:
	case PARSE_EVENTS__TERM_TYPE_MAX_STACK:
	case PARSE_EVENTS__TERM_TYPE_MAX_EVENTS:
	case PARSE_EVENTS__TERM_TYPE_OVERWRITE:
	case PARSE_EVENTS__TERM_TYPE_NOOVERWRITE:
	case PARSE_EVENTS__TERM_TYPE_AUX_OUTPUT:
		return config_term_common(attr, term, err);
	default:
		if (err) {
			err->idx = term->err_term;
			err->str = strdup("unknown term");
			err->help = strdup("valid terms: call-graph,stack-size\n");
		}
		return -EINVAL;
	}

	return 0;
}