#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bpf_program {scalar_t__ idx; char const* section_name; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ text_shndx; int /*<<< orphan*/  strtabidx; int /*<<< orphan*/  elf; TYPE_3__* symbols; } ;
struct bpf_object {size_t nr_programs; TYPE_1__ efile; struct bpf_program* programs; } ;
struct TYPE_8__ {int d_size; } ;
struct TYPE_7__ {scalar_t__ st_shndx; int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_2__ GElf_Sym ;
typedef  TYPE_3__ Elf_Data ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ GELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int LIBBPF_ERRNO__LIBELF ; 
 scalar_t__ STB_GLOBAL ; 
 char* elf_strptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_getsym (TYPE_3__*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static int
bpf_object__init_prog_names(struct bpf_object *obj)
{
	Elf_Data *symbols = obj->efile.symbols;
	struct bpf_program *prog;
	size_t pi, si;

	for (pi = 0; pi < obj->nr_programs; pi++) {
		const char *name = NULL;

		prog = &obj->programs[pi];

		for (si = 0; si < symbols->d_size / sizeof(GElf_Sym) && !name;
		     si++) {
			GElf_Sym sym;

			if (!gelf_getsym(symbols, si, &sym))
				continue;
			if (sym.st_shndx != prog->idx)
				continue;
			if (GELF_ST_BIND(sym.st_info) != STB_GLOBAL)
				continue;

			name = elf_strptr(obj->efile.elf,
					  obj->efile.strtabidx,
					  sym.st_name);
			if (!name) {
				pr_warning("failed to get sym name string for prog %s\n",
					   prog->section_name);
				return -LIBBPF_ERRNO__LIBELF;
			}
		}

		if (!name && prog->idx == obj->efile.text_shndx)
			name = ".text";

		if (!name) {
			pr_warning("failed to find sym for prog %s\n",
				   prog->section_name);
			return -EINVAL;
		}

		prog->name = strdup(name);
		if (!prog->name) {
			pr_warning("failed to allocate memory for prog sym %s\n",
				   name);
			return -ENOMEM;
		}
	}

	return 0;
}