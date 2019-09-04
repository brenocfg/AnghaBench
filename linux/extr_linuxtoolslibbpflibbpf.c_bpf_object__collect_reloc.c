#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bpf_program {int dummy; } ;
struct TYPE_6__ {int nr_reloc; TYPE_1__* reloc; } ;
struct bpf_object {TYPE_2__ efile; } ;
struct TYPE_7__ {int sh_info; scalar_t__ sh_type; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; TYPE_3__ shdr; } ;
typedef  TYPE_3__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Data ;

/* Variables and functions */
 int LIBBPF_ERRNO__INTERNAL ; 
 int LIBBPF_ERRNO__RELOC ; 
 scalar_t__ SHT_REL ; 
 struct bpf_program* bpf_object__find_prog_by_idx (struct bpf_object*,int) ; 
 int bpf_program__collect_reloc (struct bpf_program*,TYPE_3__*,int /*<<< orphan*/ *,struct bpf_object*) ; 
 int /*<<< orphan*/  obj_elf_valid (struct bpf_object*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 

__attribute__((used)) static int bpf_object__collect_reloc(struct bpf_object *obj)
{
	int i, err;

	if (!obj_elf_valid(obj)) {
		pr_warning("Internal error: elf object is closed\n");
		return -LIBBPF_ERRNO__INTERNAL;
	}

	for (i = 0; i < obj->efile.nr_reloc; i++) {
		GElf_Shdr *shdr = &obj->efile.reloc[i].shdr;
		Elf_Data *data = obj->efile.reloc[i].data;
		int idx = shdr->sh_info;
		struct bpf_program *prog;

		if (shdr->sh_type != SHT_REL) {
			pr_warning("internal error at %d\n", __LINE__);
			return -LIBBPF_ERRNO__INTERNAL;
		}

		prog = bpf_object__find_prog_by_idx(obj, idx);
		if (!prog) {
			pr_warning("relocation failed: no section(%d)\n", idx);
			return -LIBBPF_ERRNO__RELOC;
		}

		err = bpf_program__collect_reloc(prog,
						 shdr, data,
						 obj);
		if (err)
			return err;
	}
	return 0;
}