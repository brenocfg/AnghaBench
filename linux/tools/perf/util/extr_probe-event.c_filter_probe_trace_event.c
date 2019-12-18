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
struct strfilter {int dummy; } ;
struct probe_trace_event {char* event; int /*<<< orphan*/  group; } ;

/* Variables and functions */
 scalar_t__ e_snprintf (char*,int,char*,int /*<<< orphan*/ ,char*) ; 
 int strfilter__compare (struct strfilter*,char*) ; 

__attribute__((used)) static bool filter_probe_trace_event(struct probe_trace_event *tev,
				     struct strfilter *filter)
{
	char tmp[128];

	/* At first, check the event name itself */
	if (strfilter__compare(filter, tev->event))
		return true;

	/* Next, check the combination of name and group */
	if (e_snprintf(tmp, 128, "%s:%s", tev->group, tev->event) < 0)
		return false;
	return strfilter__compare(filter, tmp);
}