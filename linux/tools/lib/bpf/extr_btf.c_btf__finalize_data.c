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
struct btf_type {int dummy; } ;
struct btf {size_t nr_types; struct btf_type** types; } ;
struct bpf_object {int dummy; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 int btf_fixup_datasec (struct bpf_object*,struct btf*,struct btf_type*) ; 
 scalar_t__ btf_is_datasec (struct btf_type*) ; 

int btf__finalize_data(struct bpf_object *obj, struct btf *btf)
{
	int err = 0;
	__u32 i;

	for (i = 1; i <= btf->nr_types; i++) {
		struct btf_type *t = btf->types[i];

		/* Loader needs to fix up some of the things compiler
		 * couldn't get its hands on while emitting BTF. This
		 * is section size and global variable offset. We use
		 * the info from the ELF itself for this purpose.
		 */
		if (btf_is_datasec(t)) {
			err = btf_fixup_datasec(obj, btf, t);
			if (err)
				break;
		}
	}

	return err;
}