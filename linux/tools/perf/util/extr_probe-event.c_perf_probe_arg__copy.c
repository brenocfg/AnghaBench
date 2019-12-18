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
struct perf_probe_arg_field {struct perf_probe_arg_field* next; int /*<<< orphan*/  ref; int /*<<< orphan*/  index; void* name; } ;
struct perf_probe_arg {struct perf_probe_arg_field* field; void* type; void* var; void* name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  out_err ; 
 void* strdup_or_goto (void*,int /*<<< orphan*/ ) ; 
 struct perf_probe_arg_field* zalloc (int) ; 

__attribute__((used)) static int perf_probe_arg__copy(struct perf_probe_arg *dst,
				struct perf_probe_arg *src)
{
	struct perf_probe_arg_field *field, **ppfield;

	dst->name = strdup_or_goto(src->name, out_err);
	dst->var = strdup_or_goto(src->var, out_err);
	dst->type = strdup_or_goto(src->type, out_err);

	field = src->field;
	ppfield = &(dst->field);
	while (field) {
		*ppfield = zalloc(sizeof(*field));
		if (!*ppfield)
			goto out_err;
		(*ppfield)->name = strdup_or_goto(field->name, out_err);
		(*ppfield)->index = field->index;
		(*ppfield)->ref = field->ref;
		field = field->next;
		ppfield = &((*ppfield)->next);
	}
	return 0;
out_err:
	return -ENOMEM;
}