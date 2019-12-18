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
struct synth_event {char const* name; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 char const* SYNTH_SYSTEM ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 struct synth_event* to_synth_event (struct dyn_event*) ; 

__attribute__((used)) static bool synth_event_match(const char *system, const char *event,
			int argc, const char **argv, struct dyn_event *ev)
{
	struct synth_event *sev = to_synth_event(ev);

	return strcmp(sev->name, event) == 0 &&
		(!system || strcmp(system, SYNTH_SYSTEM) == 0);
}