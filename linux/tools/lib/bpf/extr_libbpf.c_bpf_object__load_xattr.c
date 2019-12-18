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
struct bpf_object_load_attr {int /*<<< orphan*/  log_level; int /*<<< orphan*/  target_btf_path; struct bpf_object* obj; } ;
struct bpf_object {int loaded; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERR (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bpf_object__create_maps (struct bpf_object*) ; 
 int /*<<< orphan*/  bpf_object__load_progs (struct bpf_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_object__relocate (struct bpf_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_object__unload (struct bpf_object*) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 

int bpf_object__load_xattr(struct bpf_object_load_attr *attr)
{
	struct bpf_object *obj;
	int err;

	if (!attr)
		return -EINVAL;
	obj = attr->obj;
	if (!obj)
		return -EINVAL;

	if (obj->loaded) {
		pr_warning("object should not be loaded twice\n");
		return -EINVAL;
	}

	obj->loaded = true;

	CHECK_ERR(bpf_object__create_maps(obj), err, out);
	CHECK_ERR(bpf_object__relocate(obj, attr->target_btf_path), err, out);
	CHECK_ERR(bpf_object__load_progs(obj, attr->log_level), err, out);

	return 0;
out:
	bpf_object__unload(obj);
	pr_warning("failed to load object '%s'\n", obj->path);
	return err;
}