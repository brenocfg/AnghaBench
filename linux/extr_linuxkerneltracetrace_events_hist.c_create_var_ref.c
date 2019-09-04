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
struct hist_field {int /*<<< orphan*/  hist_data; } ;

/* Variables and functions */
 unsigned long HIST_FIELD_FL_VAR_REF ; 
 struct hist_field* create_hist_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_hist_field (struct hist_field*,int /*<<< orphan*/ ) ; 
 scalar_t__ init_var_ref (struct hist_field*,struct hist_field*,char*,char*) ; 

__attribute__((used)) static struct hist_field *create_var_ref(struct hist_field *var_field,
					 char *system, char *event_name)
{
	unsigned long flags = HIST_FIELD_FL_VAR_REF;
	struct hist_field *ref_field;

	ref_field = create_hist_field(var_field->hist_data, NULL, flags, NULL);
	if (ref_field) {
		if (init_var_ref(ref_field, var_field, system, event_name)) {
			destroy_hist_field(ref_field, 0);
			return NULL;
		}
	}

	return ref_field;
}