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
struct bpf_object {int dummy; } ;
struct TYPE_2__ {scalar_t__ dump_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_LOADER_ERRNO__COMPILE ; 
 struct bpf_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct bpf_object*) ; 
 struct bpf_object* bpf_object__open (char const*) ; 
 struct bpf_object* bpf_object__open_buffer (void*,size_t,char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int libbpf_initialized ; 
 int /*<<< orphan*/  libbpf_perf_print ; 
 int /*<<< orphan*/  libbpf_set_print (int /*<<< orphan*/ ) ; 
 int llvm__compile_bpf (char const*,void**,size_t*) ; 
 int /*<<< orphan*/  llvm__dump_obj (char const*,void*,size_t) ; 
 TYPE_1__ llvm_param ; 
 int /*<<< orphan*/  perf_clang__cleanup () ; 
 int perf_clang__compile_bpf (char const*,void**,size_t*) ; 
 int /*<<< orphan*/  perf_clang__init () ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

struct bpf_object *bpf__prepare_load(const char *filename, bool source)
{
	struct bpf_object *obj;

	if (!libbpf_initialized) {
		libbpf_set_print(libbpf_perf_print);
		libbpf_initialized = true;
	}

	if (source) {
		int err;
		void *obj_buf;
		size_t obj_buf_sz;

		perf_clang__init();
		err = perf_clang__compile_bpf(filename, &obj_buf, &obj_buf_sz);
		perf_clang__cleanup();
		if (err) {
			pr_debug("bpf: builtin compilation failed: %d, try external compiler\n", err);
			err = llvm__compile_bpf(filename, &obj_buf, &obj_buf_sz);
			if (err)
				return ERR_PTR(-BPF_LOADER_ERRNO__COMPILE);
		} else
			pr_debug("bpf: successful builtin compilation\n");
		obj = bpf_object__open_buffer(obj_buf, obj_buf_sz, filename);

		if (!IS_ERR_OR_NULL(obj) && llvm_param.dump_obj)
			llvm__dump_obj(filename, obj_buf, obj_buf_sz);

		free(obj_buf);
	} else
		obj = bpf_object__open(filename);

	if (IS_ERR_OR_NULL(obj)) {
		pr_debug("bpf: failed to load %s\n", filename);
		return obj;
	}

	return obj;
}