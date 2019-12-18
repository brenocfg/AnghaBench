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
struct tep_format_field {unsigned long flags; int /*<<< orphan*/  name; int /*<<< orphan*/  arraylen; struct tep_format_field* next; } ;
struct ctf_writer {int dummy; } ;
struct bt_ctf_field_type {int dummy; } ;
struct bt_ctf_event_class {int dummy; } ;

/* Variables and functions */
 unsigned long TEP_FIELD_IS_ARRAY ; 
 unsigned long TEP_FIELD_IS_STRING ; 
 struct bt_ctf_field_type* bt_ctf_field_type_array_create (struct bt_ctf_field_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_ctf_field_type_put (struct bt_ctf_field_type*) ; 
 int event_class_add_field (struct bt_ctf_event_class*,struct bt_ctf_field_type*,struct tep_format_field*) ; 
 struct bt_ctf_field_type* get_tracepoint_field_type (struct ctf_writer*,struct tep_format_field*) ; 
 int /*<<< orphan*/  pr2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int add_tracepoint_fields_types(struct ctf_writer *cw,
				       struct tep_format_field *fields,
				       struct bt_ctf_event_class *event_class)
{
	struct tep_format_field *field;
	int ret;

	for (field = fields; field; field = field->next) {
		struct bt_ctf_field_type *type;
		unsigned long flags = field->flags;

		pr2("  field '%s'\n", field->name);

		type = get_tracepoint_field_type(cw, field);
		if (!type)
			return -1;

		/*
		 * A string is an array of chars. For this we use the string
		 * type and don't care that it is an array. What we don't
		 * support is an array of strings.
		 */
		if (flags & TEP_FIELD_IS_STRING)
			flags &= ~TEP_FIELD_IS_ARRAY;

		if (flags & TEP_FIELD_IS_ARRAY)
			type = bt_ctf_field_type_array_create(type, field->arraylen);

		ret = event_class_add_field(event_class, type, field);

		if (flags & TEP_FIELD_IS_ARRAY)
			bt_ctf_field_type_put(type);

		if (ret) {
			pr_err("Failed to add field '%s': %d\n",
					field->name, ret);
			return -1;
		}
	}

	return 0;
}