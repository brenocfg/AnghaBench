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
struct bpf_object {int /*<<< orphan*/ * btf_ext; int /*<<< orphan*/ * btf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_ELF_SEC ; 
 scalar_t__ bpf_object__is_btf_mandatory (struct bpf_object*) ; 
 int /*<<< orphan*/  bpf_object__sanitize_btf (struct bpf_object*) ; 
 int /*<<< orphan*/  bpf_object__sanitize_btf_ext (struct bpf_object*) ; 
 int /*<<< orphan*/  btf__free (int /*<<< orphan*/ *) ; 
 int btf__load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btf_ext__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bpf_object__sanitize_and_load_btf(struct bpf_object *obj)
{
	int err = 0;

	if (!obj->btf)
		return 0;

	bpf_object__sanitize_btf(obj);
	bpf_object__sanitize_btf_ext(obj);

	err = btf__load(obj->btf);
	if (err) {
		pr_warning("Error loading %s into kernel: %d.\n",
			   BTF_ELF_SEC, err);
		btf__free(obj->btf);
		obj->btf = NULL;
		/* btf_ext can't exist without btf, so free it as well */
		if (obj->btf_ext) {
			btf_ext__free(obj->btf_ext);
			obj->btf_ext = NULL;
		}

		if (bpf_object__is_btf_mandatory(obj))
			return err;
	}
	return 0;
}