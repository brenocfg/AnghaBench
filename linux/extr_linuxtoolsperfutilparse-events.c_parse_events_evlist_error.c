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
struct parse_events_state {struct parse_events_error* error; } ;
struct parse_events_error {int idx; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

void parse_events_evlist_error(struct parse_events_state *parse_state,
			       int idx, const char *str)
{
	struct parse_events_error *err = parse_state->error;

	if (!err)
		return;
	err->idx = idx;
	err->str = strdup(str);
	WARN_ONCE(!err->str, "WARNING: failed to allocate error string");
}