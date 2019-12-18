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
typedef  scalar_t__ u64 ;
struct tracing_map_elt {struct hist_elt_data* private_data; } ;
struct ring_buffer_event {int dummy; } ;
struct TYPE_2__ {unsigned int idx; } ;
struct hist_field {int flags; TYPE_1__ var; scalar_t__ (* fn ) (struct hist_field*,struct tracing_map_elt*,struct ring_buffer_event*,void*) ;} ;
struct hist_elt_data {char** field_var_str; } ;
struct field_var {struct hist_field* val; struct hist_field* var; } ;

/* Variables and functions */
 int HIST_FIELD_FL_STRING ; 
 int /*<<< orphan*/  STR_VAR_LEN_MAX ; 
 int /*<<< orphan*/  strscpy (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct hist_field*,struct tracing_map_elt*,struct ring_buffer_event*,void*) ; 
 int /*<<< orphan*/  tracing_map_set_var (struct tracing_map_elt*,unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void __update_field_vars(struct tracing_map_elt *elt,
				       struct ring_buffer_event *rbe,
				       void *rec,
				       struct field_var **field_vars,
				       unsigned int n_field_vars,
				       unsigned int field_var_str_start)
{
	struct hist_elt_data *elt_data = elt->private_data;
	unsigned int i, j, var_idx;
	u64 var_val;

	for (i = 0, j = field_var_str_start; i < n_field_vars; i++) {
		struct field_var *field_var = field_vars[i];
		struct hist_field *var = field_var->var;
		struct hist_field *val = field_var->val;

		var_val = val->fn(val, elt, rbe, rec);
		var_idx = var->var.idx;

		if (val->flags & HIST_FIELD_FL_STRING) {
			char *str = elt_data->field_var_str[j++];
			char *val_str = (char *)(uintptr_t)var_val;

			strscpy(str, val_str, STR_VAR_LEN_MAX);
			var_val = (u64)(uintptr_t)str;
		}
		tracing_map_set_var(elt, var_idx, var_val);
	}
}