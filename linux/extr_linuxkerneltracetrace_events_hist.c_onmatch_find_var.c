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
struct hist_trigger_data {int dummy; } ;
struct hist_field {int dummy; } ;
struct TYPE_2__ {char* match_event_system; char* match_event; } ;
struct action_data {TYPE_1__ onmatch; } ;

/* Variables and functions */
 struct hist_field* find_event_var (struct hist_trigger_data*,char*,char*,char*) ; 
 struct hist_field* find_target_event_var (struct hist_trigger_data*,char*,char*,char*) ; 
 int /*<<< orphan*/  hist_err_event (char*,char*,char*,char*) ; 

__attribute__((used)) static struct hist_field *
onmatch_find_var(struct hist_trigger_data *hist_data, struct action_data *data,
		 char *system, char *event, char *var)
{
	struct hist_field *hist_field;

	var++; /* skip '$' */

	hist_field = find_target_event_var(hist_data, system, event, var);
	if (!hist_field) {
		if (!system) {
			system = data->onmatch.match_event_system;
			event = data->onmatch.match_event;
		}

		hist_field = find_event_var(hist_data, system, event, var);
	}

	if (!hist_field)
		hist_err_event("onmatch: Couldn't find onmatch param: $", system, event, var);

	return hist_field;
}