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
struct tep_event {int /*<<< orphan*/  name; int /*<<< orphan*/  system; } ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_match(struct tep_event *event,
		       regex_t *sreg, regex_t *ereg)
{
	if (sreg) {
		return !regexec(sreg, event->system, 0, NULL, 0) &&
			!regexec(ereg, event->name, 0, NULL, 0);
	}

	return !regexec(ereg, event->system, 0, NULL, 0) ||
		!regexec(ereg, event->name, 0, NULL, 0);
}