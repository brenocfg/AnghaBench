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
struct bpf_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct bpf_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct bpf_object*) ; 
 struct bpf_object* bpf_object__open_buffer (void*,size_t,char const*) ; 
 int libbpf_initialized ; 
 int /*<<< orphan*/  libbpf_perf_print ; 
 int /*<<< orphan*/  libbpf_set_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

struct bpf_object *
bpf__prepare_load_buffer(void *obj_buf, size_t obj_buf_sz, const char *name)
{
	struct bpf_object *obj;

	if (!libbpf_initialized) {
		libbpf_set_print(libbpf_perf_print);
		libbpf_initialized = true;
	}

	obj = bpf_object__open_buffer(obj_buf, obj_buf_sz, name);
	if (IS_ERR_OR_NULL(obj)) {
		pr_debug("bpf: failed to load buffer\n");
		return ERR_PTR(-EINVAL);
	}

	return obj;
}