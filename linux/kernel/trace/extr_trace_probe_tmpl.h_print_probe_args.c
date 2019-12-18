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
typedef  void u8 ;
struct trace_seq {int dummy; } ;
struct probe_arg {int count; int offset; TYPE_1__* type; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  (* print ) (struct trace_seq*,void*,void*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct trace_seq*,void*,void*) ; 
 int /*<<< orphan*/  stub2 (struct trace_seq*,void*,void*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 

__attribute__((used)) static inline int
print_probe_args(struct trace_seq *s, struct probe_arg *args, int nr_args,
		 u8 *data, void *field)
{
	void *p;
	int i, j;

	for (i = 0; i < nr_args; i++) {
		struct probe_arg *a = args + i;

		trace_seq_printf(s, " %s=", a->name);
		if (likely(!a->count)) {
			if (!a->type->print(s, data + a->offset, field))
				return -ENOMEM;
			continue;
		}
		trace_seq_putc(s, '{');
		p = data + a->offset;
		for (j = 0; j < a->count; j++) {
			if (!a->type->print(s, p, field))
				return -ENOMEM;
			trace_seq_putc(s, j == a->count - 1 ? '}' : ',');
			p += a->type->size;
		}
	}
	return 0;
}