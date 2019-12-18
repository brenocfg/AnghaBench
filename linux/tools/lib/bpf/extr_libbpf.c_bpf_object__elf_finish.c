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
struct TYPE_2__ {scalar_t__ obj_buf_sz; int /*<<< orphan*/ * obj_buf; int /*<<< orphan*/  fd; scalar_t__ nr_reloc; int /*<<< orphan*/  reloc; int /*<<< orphan*/ * bss; int /*<<< orphan*/ * rodata; int /*<<< orphan*/ * data; int /*<<< orphan*/ * symbols; int /*<<< orphan*/ * elf; } ;
struct bpf_object {TYPE_1__ efile; } ;

/* Variables and functions */
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obj_elf_valid (struct bpf_object*) ; 
 int /*<<< orphan*/  zclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpf_object__elf_finish(struct bpf_object *obj)
{
	if (!obj_elf_valid(obj))
		return;

	if (obj->efile.elf) {
		elf_end(obj->efile.elf);
		obj->efile.elf = NULL;
	}
	obj->efile.symbols = NULL;
	obj->efile.data = NULL;
	obj->efile.rodata = NULL;
	obj->efile.bss = NULL;

	zfree(&obj->efile.reloc);
	obj->efile.nr_reloc = 0;
	zclose(obj->efile.fd);
	obj->efile.obj_buf = NULL;
	obj->efile.obj_buf_sz = 0;
}