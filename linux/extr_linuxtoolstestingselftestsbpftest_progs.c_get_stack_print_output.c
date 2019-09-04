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
struct ksym {int /*<<< orphan*/  name; } ;
struct get_stack_trace_t {int kern_stack_size; scalar_t__* kern_stack; scalar_t__ user_stack_size; scalar_t__ user_stack_buildid_size; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int LIBBPF_PERF_EVENT_CONT ; 
 int LIBBPF_PERF_EVENT_DONE ; 
 int LIBBPF_PERF_EVENT_ERROR ; 
 scalar_t__ MAX_CNT_RAWTP ; 
 scalar_t__ jit_enabled ; 
 struct ksym* ksym_search (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int get_stack_print_output(void *data, int size)
{
	bool good_kern_stack = false, good_user_stack = false;
	const char *nonjit_func = "___bpf_prog_run";
	struct get_stack_trace_t *e = data;
	int i, num_stack;
	static __u64 cnt;
	struct ksym *ks;

	cnt++;

	if (size < sizeof(struct get_stack_trace_t)) {
		__u64 *raw_data = data;
		bool found = false;

		num_stack = size / sizeof(__u64);
		/* If jit is enabled, we do not have a good way to
		 * verify the sanity of the kernel stack. So we
		 * just assume it is good if the stack is not empty.
		 * This could be improved in the future.
		 */
		if (jit_enabled) {
			found = num_stack > 0;
		} else {
			for (i = 0; i < num_stack; i++) {
				ks = ksym_search(raw_data[i]);
				if (strcmp(ks->name, nonjit_func) == 0) {
					found = true;
					break;
				}
			}
		}
		if (found) {
			good_kern_stack = true;
			good_user_stack = true;
		}
	} else {
		num_stack = e->kern_stack_size / sizeof(__u64);
		if (jit_enabled) {
			good_kern_stack = num_stack > 0;
		} else {
			for (i = 0; i < num_stack; i++) {
				ks = ksym_search(e->kern_stack[i]);
				if (strcmp(ks->name, nonjit_func) == 0) {
					good_kern_stack = true;
					break;
				}
			}
		}
		if (e->user_stack_size > 0 && e->user_stack_buildid_size > 0)
			good_user_stack = true;
	}
	if (!good_kern_stack || !good_user_stack)
		return LIBBPF_PERF_EVENT_ERROR;

	if (cnt == MAX_CNT_RAWTP)
		return LIBBPF_PERF_EVENT_DONE;

	return LIBBPF_PERF_EVENT_CONT;
}