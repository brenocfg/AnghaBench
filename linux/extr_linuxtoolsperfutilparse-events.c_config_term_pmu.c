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
struct parse_events_term {scalar_t__ type_term; } ;
struct parse_events_error {int dummy; } ;

/* Variables and functions */
 scalar_t__ PARSE_EVENTS__TERM_TYPE_DRV_CFG ; 
 scalar_t__ PARSE_EVENTS__TERM_TYPE_USER ; 
 int config_term_common (struct perf_event_attr*,struct parse_events_term*,struct parse_events_error*) ; 

__attribute__((used)) static int config_term_pmu(struct perf_event_attr *attr,
			   struct parse_events_term *term,
			   struct parse_events_error *err)
{
	if (term->type_term == PARSE_EVENTS__TERM_TYPE_USER ||
	    term->type_term == PARSE_EVENTS__TERM_TYPE_DRV_CFG)
		/*
		 * Always succeed for sysfs terms, as we dont know
		 * at this point what type they need to have.
		 */
		return 0;
	else
		return config_term_common(attr, term, err);
}