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
struct hist_trigger_data {int dummy; } ;
struct hist_field {int dummy; } ;

/* Variables and functions */
 struct hist_field* create_var_ref (struct hist_field*,char*,char*) ; 
 struct hist_field* find_event_var (struct hist_trigger_data*,char*,char*,char*) ; 
 int /*<<< orphan*/  hist_err_event (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  is_var_ref (char*) ; 

__attribute__((used)) static struct hist_field *parse_var_ref(struct hist_trigger_data *hist_data,
					char *system, char *event_name,
					char *var_name)
{
	struct hist_field *var_field = NULL, *ref_field = NULL;

	if (!is_var_ref(var_name))
		return NULL;

	var_name++;

	var_field = find_event_var(hist_data, system, event_name, var_name);
	if (var_field)
		ref_field = create_var_ref(var_field, system, event_name);

	if (!ref_field)
		hist_err_event("Couldn't find variable: $",
			       system, event_name, var_name);

	return ref_field;
}