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
struct TYPE_2__ {char* name; int /*<<< orphan*/  hist_data; int /*<<< orphan*/  idx; } ;
struct hist_field {int flags; char* system; char* event_name; char* name; char* type; TYPE_1__ var; int /*<<< orphan*/  is_signed; int /*<<< orphan*/  size; int /*<<< orphan*/  hist_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIST_FIELD_FL_TIMESTAMP ; 
 int HIST_FIELD_FL_TIMESTAMP_USECS ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_var_ref(struct hist_field *ref_field,
			struct hist_field *var_field,
			char *system, char *event_name)
{
	int err = 0;

	ref_field->var.idx = var_field->var.idx;
	ref_field->var.hist_data = var_field->hist_data;
	ref_field->size = var_field->size;
	ref_field->is_signed = var_field->is_signed;
	ref_field->flags |= var_field->flags &
		(HIST_FIELD_FL_TIMESTAMP | HIST_FIELD_FL_TIMESTAMP_USECS);

	if (system) {
		ref_field->system = kstrdup(system, GFP_KERNEL);
		if (!ref_field->system)
			return -ENOMEM;
	}

	if (event_name) {
		ref_field->event_name = kstrdup(event_name, GFP_KERNEL);
		if (!ref_field->event_name) {
			err = -ENOMEM;
			goto free;
		}
	}

	if (var_field->var.name) {
		ref_field->name = kstrdup(var_field->var.name, GFP_KERNEL);
		if (!ref_field->name) {
			err = -ENOMEM;
			goto free;
		}
	} else if (var_field->name) {
		ref_field->name = kstrdup(var_field->name, GFP_KERNEL);
		if (!ref_field->name) {
			err = -ENOMEM;
			goto free;
		}
	}

	ref_field->type = kstrdup(var_field->type, GFP_KERNEL);
	if (!ref_field->type) {
		err = -ENOMEM;
		goto free;
	}
 out:
	return err;
 free:
	kfree(ref_field->system);
	kfree(ref_field->event_name);
	kfree(ref_field->name);

	goto out;
}