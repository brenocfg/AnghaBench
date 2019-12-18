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
struct tep_handle {int nr_events; struct tep_event** events; } ;
struct tep_event {int dummy; } ;
struct event_list {int dummy; } ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int REG_ICASE ; 
 int REG_NOSUB ; 
 int TEP_ERRNO__EVENT_NOT_FOUND ; 
 int TEP_ERRNO__INVALID_EVENT_NAME ; 
 int TEP_ERRNO__MEM_ALLOC_FAILED ; 
 scalar_t__ add_event (struct event_list**,struct tep_event*) ; 
 int asprintf (char**,char*,char*) ; 
 scalar_t__ event_match (struct tep_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum tep_errno
find_event(struct tep_handle *tep, struct event_list **events,
	   char *sys_name, char *event_name)
{
	struct tep_event *event;
	regex_t ereg;
	regex_t sreg;
	int match = 0;
	int fail = 0;
	char *reg;
	int ret;
	int i;

	if (!event_name) {
		/* if no name is given, then swap sys and name */
		event_name = sys_name;
		sys_name = NULL;
	}

	ret = asprintf(&reg, "^%s$", event_name);
	if (ret < 0)
		return TEP_ERRNO__MEM_ALLOC_FAILED;

	ret = regcomp(&ereg, reg, REG_ICASE|REG_NOSUB);
	free(reg);

	if (ret)
		return TEP_ERRNO__INVALID_EVENT_NAME;

	if (sys_name) {
		ret = asprintf(&reg, "^%s$", sys_name);
		if (ret < 0) {
			regfree(&ereg);
			return TEP_ERRNO__MEM_ALLOC_FAILED;
		}

		ret = regcomp(&sreg, reg, REG_ICASE|REG_NOSUB);
		free(reg);
		if (ret) {
			regfree(&ereg);
			return TEP_ERRNO__INVALID_EVENT_NAME;
		}
	}

	for (i = 0; i < tep->nr_events; i++) {
		event = tep->events[i];
		if (event_match(event, sys_name ? &sreg : NULL, &ereg)) {
			match = 1;
			if (add_event(events, event) < 0) {
				fail = 1;
				break;
			}
		}
	}

	regfree(&ereg);
	if (sys_name)
		regfree(&sreg);

	if (!match)
		return TEP_ERRNO__EVENT_NOT_FOUND;
	if (fail)
		return TEP_ERRNO__MEM_ALLOC_FAILED;

	return 0;
}