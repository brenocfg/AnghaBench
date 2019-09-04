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
struct bpf_object {size_t nr_programs; int /*<<< orphan*/  kern_version; int /*<<< orphan*/  license; int /*<<< orphan*/ * programs; } ;

/* Variables and functions */
 scalar_t__ bpf_program__is_function_storage (int /*<<< orphan*/ *,struct bpf_object*) ; 
 int bpf_program__load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bpf_object__load_progs(struct bpf_object *obj)
{
	size_t i;
	int err;

	for (i = 0; i < obj->nr_programs; i++) {
		if (bpf_program__is_function_storage(&obj->programs[i], obj))
			continue;
		err = bpf_program__load(&obj->programs[i],
					obj->license,
					obj->kern_version);
		if (err)
			return err;
	}
	return 0;
}