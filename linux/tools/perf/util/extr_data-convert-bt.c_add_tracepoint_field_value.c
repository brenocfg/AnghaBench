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
struct tep_format_field {char* name; unsigned long flags; char* alias; unsigned int offset; unsigned int size; unsigned int arraylen; TYPE_1__* event; } ;
struct perf_sample {void* raw_data; } ;
struct ctf_writer {int dummy; } ;
struct bt_ctf_field_type {int dummy; } ;
struct bt_ctf_field {int dummy; } ;
struct bt_ctf_event_class {int dummy; } ;
struct bt_ctf_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tep; } ;

/* Variables and functions */
 unsigned long TEP_FIELD_IS_ARRAY ; 
 unsigned long TEP_FIELD_IS_DYNAMIC ; 
 unsigned long TEP_FIELD_IS_SIGNED ; 
 unsigned long TEP_FIELD_IS_STRING ; 
 int /*<<< orphan*/  adjust_signedness (unsigned long long,unsigned int) ; 
 struct bt_ctf_field_type* bt_ctf_event_class_get_field_by_name (struct bt_ctf_event_class*,char const*) ; 
 int bt_ctf_event_set_payload (struct bt_ctf_event*,char const*,struct bt_ctf_field*) ; 
 struct bt_ctf_field* bt_ctf_field_array_get_field (struct bt_ctf_field*,unsigned int) ; 
 struct bt_ctf_field* bt_ctf_field_create (struct bt_ctf_field_type*) ; 
 int /*<<< orphan*/  bt_ctf_field_put (struct bt_ctf_field*) ; 
 int bt_ctf_field_signed_integer_set_value (struct bt_ctf_field*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_ctf_field_type_put (struct bt_ctf_field_type*) ; 
 int bt_ctf_field_unsigned_integer_set_value (struct bt_ctf_field*,unsigned long long) ; 
 struct bt_ctf_field_type* get_tracepoint_field_type (struct ctf_writer*,struct tep_format_field*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int string_set_value (struct bt_ctf_field*,void*) ; 
 unsigned long long tep_read_number (int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static int add_tracepoint_field_value(struct ctf_writer *cw,
				      struct bt_ctf_event_class *event_class,
				      struct bt_ctf_event *event,
				      struct perf_sample *sample,
				      struct tep_format_field *fmtf)
{
	struct bt_ctf_field_type *type;
	struct bt_ctf_field *array_field;
	struct bt_ctf_field *field;
	const char *name = fmtf->name;
	void *data = sample->raw_data;
	unsigned long flags = fmtf->flags;
	unsigned int n_items;
	unsigned int i;
	unsigned int offset;
	unsigned int len;
	int ret;

	name = fmtf->alias;
	offset = fmtf->offset;
	len = fmtf->size;
	if (flags & TEP_FIELD_IS_STRING)
		flags &= ~TEP_FIELD_IS_ARRAY;

	if (flags & TEP_FIELD_IS_DYNAMIC) {
		unsigned long long tmp_val;

		tmp_val = tep_read_number(fmtf->event->tep,
					  data + offset, len);
		offset = tmp_val;
		len = offset >> 16;
		offset &= 0xffff;
	}

	if (flags & TEP_FIELD_IS_ARRAY) {

		type = bt_ctf_event_class_get_field_by_name(
				event_class, name);
		array_field = bt_ctf_field_create(type);
		bt_ctf_field_type_put(type);
		if (!array_field) {
			pr_err("Failed to create array type %s\n", name);
			return -1;
		}

		len = fmtf->size / fmtf->arraylen;
		n_items = fmtf->arraylen;
	} else {
		n_items = 1;
		array_field = NULL;
	}

	type = get_tracepoint_field_type(cw, fmtf);

	for (i = 0; i < n_items; i++) {
		if (flags & TEP_FIELD_IS_ARRAY)
			field = bt_ctf_field_array_get_field(array_field, i);
		else
			field = bt_ctf_field_create(type);

		if (!field) {
			pr_err("failed to create a field %s\n", name);
			return -1;
		}

		if (flags & TEP_FIELD_IS_STRING)
			ret = string_set_value(field, data + offset + i * len);
		else {
			unsigned long long value_int;

			value_int = tep_read_number(
					fmtf->event->tep,
					data + offset + i * len, len);

			if (!(flags & TEP_FIELD_IS_SIGNED))
				ret = bt_ctf_field_unsigned_integer_set_value(
						field, value_int);
			else
				ret = bt_ctf_field_signed_integer_set_value(
						field, adjust_signedness(value_int, len));
		}

		if (ret) {
			pr_err("failed to set file value %s\n", name);
			goto err_put_field;
		}
		if (!(flags & TEP_FIELD_IS_ARRAY)) {
			ret = bt_ctf_event_set_payload(event, name, field);
			if (ret) {
				pr_err("failed to set payload %s\n", name);
				goto err_put_field;
			}
		}
		bt_ctf_field_put(field);
	}
	if (flags & TEP_FIELD_IS_ARRAY) {
		ret = bt_ctf_event_set_payload(event, name, array_field);
		if (ret) {
			pr_err("Failed add payload array %s\n", name);
			return -1;
		}
		bt_ctf_field_put(array_field);
	}
	return 0;

err_put_field:
	bt_ctf_field_put(field);
	return -1;
}