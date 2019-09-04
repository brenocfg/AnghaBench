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
typedef  unsigned int u64 ;
struct ip_callchain {unsigned int nr; scalar_t__ ips; } ;
struct bt_ctf_field_type {int dummy; } ;
struct bt_ctf_field {int dummy; } ;
struct bt_ctf_event_class {int dummy; } ;
struct bt_ctf_event {int dummy; } ;

/* Variables and functions */
 struct bt_ctf_field_type* bt_ctf_event_class_get_field_by_name (struct bt_ctf_event_class*,char*) ; 
 int bt_ctf_event_set_payload (struct bt_ctf_event*,char*,struct bt_ctf_field*) ; 
 struct bt_ctf_field* bt_ctf_field_create (struct bt_ctf_field_type*) ; 
 int /*<<< orphan*/  bt_ctf_field_put (struct bt_ctf_field*) ; 
 struct bt_ctf_field* bt_ctf_field_sequence_get_field (struct bt_ctf_field*,unsigned int) ; 
 int bt_ctf_field_sequence_set_length (struct bt_ctf_field*,struct bt_ctf_field*) ; 
 int /*<<< orphan*/  bt_ctf_field_type_put (struct bt_ctf_field_type*) ; 
 int bt_ctf_field_unsigned_integer_set_value (struct bt_ctf_field*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int
add_callchain_output_values(struct bt_ctf_event_class *event_class,
		      struct bt_ctf_event *event,
		      struct ip_callchain *callchain)
{
	struct bt_ctf_field_type *len_type, *seq_type;
	struct bt_ctf_field *len_field, *seq_field;
	unsigned int nr_elements = callchain->nr;
	unsigned int i;
	int ret;

	len_type = bt_ctf_event_class_get_field_by_name(
			event_class, "perf_callchain_size");
	len_field = bt_ctf_field_create(len_type);
	if (!len_field) {
		pr_err("failed to create 'perf_callchain_size' for callchain output event\n");
		ret = -1;
		goto put_len_type;
	}

	ret = bt_ctf_field_unsigned_integer_set_value(len_field, nr_elements);
	if (ret) {
		pr_err("failed to set field value for perf_callchain_size\n");
		goto put_len_field;
	}
	ret = bt_ctf_event_set_payload(event, "perf_callchain_size", len_field);
	if (ret) {
		pr_err("failed to set payload to perf_callchain_size\n");
		goto put_len_field;
	}

	seq_type = bt_ctf_event_class_get_field_by_name(
			event_class, "perf_callchain");
	seq_field = bt_ctf_field_create(seq_type);
	if (!seq_field) {
		pr_err("failed to create 'perf_callchain' for callchain output event\n");
		ret = -1;
		goto put_seq_type;
	}

	ret = bt_ctf_field_sequence_set_length(seq_field, len_field);
	if (ret) {
		pr_err("failed to set length of 'perf_callchain'\n");
		goto put_seq_field;
	}

	for (i = 0; i < nr_elements; i++) {
		struct bt_ctf_field *elem_field =
			bt_ctf_field_sequence_get_field(seq_field, i);

		ret = bt_ctf_field_unsigned_integer_set_value(elem_field,
				((u64 *)(callchain->ips))[i]);

		bt_ctf_field_put(elem_field);
		if (ret) {
			pr_err("failed to set callchain[%d]\n", i);
			goto put_seq_field;
		}
	}

	ret = bt_ctf_event_set_payload(event, "perf_callchain", seq_field);
	if (ret)
		pr_err("failed to set payload for raw_data\n");

put_seq_field:
	bt_ctf_field_put(seq_field);
put_seq_type:
	bt_ctf_field_type_put(seq_type);
put_len_field:
	bt_ctf_field_put(len_field);
put_len_type:
	bt_ctf_field_type_put(len_type);
	return ret;
}