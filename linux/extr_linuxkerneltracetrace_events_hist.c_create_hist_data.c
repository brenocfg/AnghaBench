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
struct tracing_map_ops {int dummy; } ;
struct trace_event_file {int dummy; } ;
struct hist_trigger_data {int remove; struct hist_trigger_attrs* attrs; int /*<<< orphan*/ * map; int /*<<< orphan*/  key_size; struct trace_event_file* event_file; } ;
struct hist_trigger_attrs {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct hist_trigger_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int create_hist_fields (struct hist_trigger_data*,struct trace_event_file*) ; 
 int create_sort_keys (struct hist_trigger_data*) ; 
 int create_tracing_map_fields (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  destroy_hist_data (struct hist_trigger_data*) ; 
 struct tracing_map_ops hist_trigger_elt_data_ops ; 
 struct hist_trigger_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int parse_actions (struct hist_trigger_data*) ; 
 int /*<<< orphan*/ * tracing_map_create (unsigned int,int /*<<< orphan*/ ,struct tracing_map_ops const*,struct hist_trigger_data*) ; 

__attribute__((used)) static struct hist_trigger_data *
create_hist_data(unsigned int map_bits,
		 struct hist_trigger_attrs *attrs,
		 struct trace_event_file *file,
		 bool remove)
{
	const struct tracing_map_ops *map_ops = NULL;
	struct hist_trigger_data *hist_data;
	int ret = 0;

	hist_data = kzalloc(sizeof(*hist_data), GFP_KERNEL);
	if (!hist_data)
		return ERR_PTR(-ENOMEM);

	hist_data->attrs = attrs;
	hist_data->remove = remove;
	hist_data->event_file = file;

	ret = parse_actions(hist_data);
	if (ret)
		goto free;

	ret = create_hist_fields(hist_data, file);
	if (ret)
		goto free;

	ret = create_sort_keys(hist_data);
	if (ret)
		goto free;

	map_ops = &hist_trigger_elt_data_ops;

	hist_data->map = tracing_map_create(map_bits, hist_data->key_size,
					    map_ops, hist_data);
	if (IS_ERR(hist_data->map)) {
		ret = PTR_ERR(hist_data->map);
		hist_data->map = NULL;
		goto free;
	}

	ret = create_tracing_map_fields(hist_data);
	if (ret)
		goto free;
 out:
	return hist_data;
 free:
	hist_data->attrs = NULL;

	destroy_hist_data(hist_data);

	hist_data = ERR_PTR(ret);

	goto out;
}