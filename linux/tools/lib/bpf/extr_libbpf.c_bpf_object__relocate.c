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
struct bpf_program {int section_name; } ;
struct bpf_object {size_t nr_programs; struct bpf_program* programs; scalar_t__ btf_ext; } ;

/* Variables and functions */
 int bpf_object__relocate_core (struct bpf_object*,char const*) ; 
 int bpf_program__relocate (struct bpf_program*,struct bpf_object*) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 

__attribute__((used)) static int
bpf_object__relocate(struct bpf_object *obj, const char *targ_btf_path)
{
	struct bpf_program *prog;
	size_t i;
	int err;

	if (obj->btf_ext) {
		err = bpf_object__relocate_core(obj, targ_btf_path);
		if (err) {
			pr_warning("failed to perform CO-RE relocations: %d\n",
				   err);
			return err;
		}
	}
	for (i = 0; i < obj->nr_programs; i++) {
		prog = &obj->programs[i];

		err = bpf_program__relocate(prog, obj);
		if (err) {
			pr_warning("failed to relocate '%s'\n",
				   prog->section_name);
			return err;
		}
	}
	return 0;
}