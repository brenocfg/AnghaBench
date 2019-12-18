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
struct TYPE_6__ {int /*<<< orphan*/  strtabidx; int /*<<< orphan*/  elf; TYPE_3__* symbols; } ;
struct bpf_object {TYPE_1__ efile; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_8__ {int d_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  st_value; int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_2__ GElf_Sym ;
typedef  TYPE_3__ Elf_Data ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 scalar_t__ GELF_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STB_GLOBAL ; 
 scalar_t__ STT_OBJECT ; 
 char* elf_strptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_getsym (TYPE_3__*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

int bpf_object__variable_offset(const struct bpf_object *obj, const char *name,
				__u32 *off)
{
	Elf_Data *symbols = obj->efile.symbols;
	const char *sname;
	size_t si;

	if (!name || !off)
		return -EINVAL;

	for (si = 0; si < symbols->d_size / sizeof(GElf_Sym); si++) {
		GElf_Sym sym;

		if (!gelf_getsym(symbols, si, &sym))
			continue;
		if (GELF_ST_BIND(sym.st_info) != STB_GLOBAL ||
		    GELF_ST_TYPE(sym.st_info) != STT_OBJECT)
			continue;

		sname = elf_strptr(obj->efile.elf, obj->efile.strtabidx,
				   sym.st_name);
		if (!sname) {
			pr_warning("failed to get sym name string for var %s\n",
				   name);
			return -EIO;
		}
		if (strcmp(name, sname) == 0) {
			*off = sym.st_value;
			return 0;
		}
	}

	return -ENOENT;
}