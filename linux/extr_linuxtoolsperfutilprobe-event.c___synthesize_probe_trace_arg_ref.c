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
struct strbuf {int dummy; } ;
struct probe_trace_arg_ref {int /*<<< orphan*/  offset; struct probe_trace_arg_ref* next; } ;

/* Variables and functions */
 int strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __synthesize_probe_trace_arg_ref(struct probe_trace_arg_ref *ref,
					    struct strbuf *buf, int depth)
{
	int err;
	if (ref->next) {
		depth = __synthesize_probe_trace_arg_ref(ref->next, buf,
							 depth + 1);
		if (depth < 0)
			return depth;
	}
	err = strbuf_addf(buf, "%+ld(", ref->offset);
	return (err < 0) ? err : depth;
}