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
typedef  int /*<<< orphan*/  u64 ;
struct tracing_map_elt {int dummy; } ;
struct hist_trigger_data {unsigned int n_var_refs; int /*<<< orphan*/  map; struct hist_field** var_refs; } ;
struct TYPE_2__ {unsigned int idx; struct hist_trigger_data* hist_data; } ;
struct hist_field {int /*<<< orphan*/  read_once; TYPE_1__ var; } ;

/* Variables and functions */
 struct tracing_map_elt* tracing_map_lookup (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tracing_map_read_var (struct tracing_map_elt*,unsigned int) ; 
 int /*<<< orphan*/  tracing_map_read_var_once (struct tracing_map_elt*,unsigned int) ; 
 int /*<<< orphan*/  tracing_map_var_set (struct tracing_map_elt*,unsigned int) ; 

__attribute__((used)) static bool resolve_var_refs(struct hist_trigger_data *hist_data, void *key,
			     u64 *var_ref_vals, bool self)
{
	struct hist_trigger_data *var_data;
	struct tracing_map_elt *var_elt;
	struct hist_field *hist_field;
	unsigned int i, var_idx;
	bool resolved = true;
	u64 var_val = 0;

	for (i = 0; i < hist_data->n_var_refs; i++) {
		hist_field = hist_data->var_refs[i];
		var_idx = hist_field->var.idx;
		var_data = hist_field->var.hist_data;

		if (var_data == NULL) {
			resolved = false;
			break;
		}

		if ((self && var_data != hist_data) ||
		    (!self && var_data == hist_data))
			continue;

		var_elt = tracing_map_lookup(var_data->map, key);
		if (!var_elt) {
			resolved = false;
			break;
		}

		if (!tracing_map_var_set(var_elt, var_idx)) {
			resolved = false;
			break;
		}

		if (self || !hist_field->read_once)
			var_val = tracing_map_read_var(var_elt, var_idx);
		else
			var_val = tracing_map_read_var_once(var_elt, var_idx);

		var_ref_vals[i] = var_val;
	}

	return resolved;
}