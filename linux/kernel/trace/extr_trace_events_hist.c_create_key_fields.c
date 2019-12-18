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
struct trace_event_file {int dummy; } ;
struct hist_trigger_data {unsigned int n_vals; TYPE_1__* attrs; } ;
struct TYPE_2__ {char* keys_str; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TRACING_MAP_KEYS_MAX ; 
 int create_key_field (struct hist_trigger_data*,unsigned int,unsigned int,struct trace_event_file*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int create_key_fields(struct hist_trigger_data *hist_data,
			     struct trace_event_file *file)
{
	unsigned int i, key_offset = 0, n_vals = hist_data->n_vals;
	char *fields_str, *field_str;
	int ret = -EINVAL;

	fields_str = hist_data->attrs->keys_str;
	if (!fields_str)
		goto out;

	strsep(&fields_str, "=");
	if (!fields_str)
		goto out;

	for (i = n_vals; i < n_vals + TRACING_MAP_KEYS_MAX; i++) {
		field_str = strsep(&fields_str, ",");
		if (!field_str)
			break;
		ret = create_key_field(hist_data, i, key_offset,
				       file, field_str);
		if (ret < 0)
			goto out;
		key_offset += ret;
	}
	if (fields_str) {
		ret = -EINVAL;
		goto out;
	}
	ret = 0;
 out:
	return ret;
}