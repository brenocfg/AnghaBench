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
typedef  unsigned int u32 ;
struct perf_sample {unsigned int raw_size; scalar_t__ raw_data; } ;
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
 int /*<<< orphan*/  pr_warning (char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int
add_bpf_output_values(struct bt_ctf_event_class *event_class,
		      struct bt_ctf_event *event,
		      struct perf_sample *sample)
{
	struct bt_ctf_field_type *len_type, *seq_type;
	struct bt_ctf_field *len_field, *seq_field;
	unsigned int raw_size = sample->raw_size;
	unsigned int nr_elements = raw_size / sizeof(u32);
	unsigned int i;
	int ret;

	if (nr_elements * sizeof(u32) != raw_size)
		pr_warning("Incorrect raw_size (%u) in bpf output event, skip %zu bytes\n",
			   raw_size, nr_elements * sizeof(u32) - raw_size);

	len_type = bt_ctf_event_class_get_field_by_name(event_class, "raw_len");
	len_field = bt_ctf_field_create(len_type);
	if (!len_field) {
		pr_err("failed to create 'raw_len' for bpf output event\n");
		ret = -1;
		goto put_len_type;
	}

	ret = bt_ctf_field_unsigned_integer_set_value(len_field, nr_elements);
	if (ret) {
		pr_err("failed to set field value for raw_len\n");
		goto put_len_field;
	}
	ret = bt_ctf_event_set_payload(event, "raw_len", len_field);
	if (ret) {
		pr_err("failed to set payload to raw_len\n");
		goto put_len_field;
	}

	seq_type = bt_ctf_event_class_get_field_by_name(event_class, "raw_data");
	seq_field = bt_ctf_field_create(seq_type);
	if (!seq_field) {
		pr_err("failed to create 'raw_data' for bpf output event\n");
		ret = -1;
		goto put_seq_type;
	}

	ret = bt_ctf_field_sequence_set_length(seq_field, len_field);
	if (ret) {
		pr_err("failed to set length of 'raw_data'\n");
		goto put_seq_field;
	}

	for (i = 0; i < nr_elements; i++) {
		struct bt_ctf_field *elem_field =
			bt_ctf_field_sequence_get_field(seq_field, i);

		ret = bt_ctf_field_unsigned_integer_set_value(elem_field,
				((u32 *)(sample->raw_data))[i]);

		bt_ctf_field_put(elem_field);
		if (ret) {
			pr_err("failed to set raw_data[%d]\n", i);
			goto put_seq_field;
		}
	}

	ret = bt_ctf_event_set_payload(event, "raw_data", seq_field);
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