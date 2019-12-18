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
struct trace_event_file {int dummy; } ;
struct hist_trigger_data {int dummy; } ;
struct hist_field {int dummy; } ;
struct ftrace_event_field {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct hist_field* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ftrace_event_field*) ; 
 int PTR_ERR (struct ftrace_event_field*) ; 
 struct hist_field* create_alias (struct hist_trigger_data*,struct hist_field*,char*) ; 
 struct hist_field* create_hist_field (struct hist_trigger_data*,struct ftrace_event_field*,unsigned long,char*) ; 
 char* local_field_var_ref (struct hist_trigger_data*,char*,char*,char*) ; 
 struct ftrace_event_field* parse_field (struct hist_trigger_data*,struct trace_event_file*,char*,unsigned long*) ; 
 struct hist_field* parse_var_ref (struct hist_trigger_data*,char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static struct hist_field *parse_atom(struct hist_trigger_data *hist_data,
				     struct trace_event_file *file, char *str,
				     unsigned long *flags, char *var_name)
{
	char *s, *ref_system = NULL, *ref_event = NULL, *ref_var = str;
	struct ftrace_event_field *field = NULL;
	struct hist_field *hist_field = NULL;
	int ret = 0;

	s = strchr(str, '.');
	if (s) {
		s = strchr(++s, '.');
		if (s) {
			ref_system = strsep(&str, ".");
			if (!str) {
				ret = -EINVAL;
				goto out;
			}
			ref_event = strsep(&str, ".");
			if (!str) {
				ret = -EINVAL;
				goto out;
			}
			ref_var = str;
		}
	}

	s = local_field_var_ref(hist_data, ref_system, ref_event, ref_var);
	if (!s) {
		hist_field = parse_var_ref(hist_data, ref_system,
					   ref_event, ref_var);
		if (hist_field) {
			if (var_name) {
				hist_field = create_alias(hist_data, hist_field, var_name);
				if (!hist_field) {
					ret = -ENOMEM;
					goto out;
				}
			}
			return hist_field;
		}
	} else
		str = s;

	field = parse_field(hist_data, file, str, flags);
	if (IS_ERR(field)) {
		ret = PTR_ERR(field);
		goto out;
	}

	hist_field = create_hist_field(hist_data, field, *flags, var_name);
	if (!hist_field) {
		ret = -ENOMEM;
		goto out;
	}

	return hist_field;
 out:
	return ERR_PTR(ret);
}