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
struct parse_events_term {scalar_t__ type_term; } ;

/* Variables and functions */
 scalar_t__ PARSE_EVENTS__TERM_TYPE_USER ; 

int parse_events__is_hardcoded_term(struct parse_events_term *term)
{
	return term->type_term != PARSE_EVENTS__TERM_TYPE_USER;
}