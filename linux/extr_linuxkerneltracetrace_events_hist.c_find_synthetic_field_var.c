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
 int /*<<< orphan*/  ENOMEM ; 
 struct hist_field* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_FILTER_STR_VAL ; 
 struct hist_field* find_event_var (struct hist_trigger_data*,char*,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static struct hist_field *
find_synthetic_field_var(struct hist_trigger_data *target_hist_data,
			 char *system, char *event_name, char *field_name)
{
	struct hist_field *event_var;
	char *synthetic_name;

	synthetic_name = kzalloc(MAX_FILTER_STR_VAL, GFP_KERNEL);
	if (!synthetic_name)
		return ERR_PTR(-ENOMEM);

	strcpy(synthetic_name, "synthetic_");
	strcat(synthetic_name, field_name);

	event_var = find_event_var(target_hist_data, system, event_name, synthetic_name);

	kfree(synthetic_name);

	return event_var;
}