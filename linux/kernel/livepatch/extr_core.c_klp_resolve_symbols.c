#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* strtab; TYPE_2__* symtab; } ;
struct module {TYPE_1__ core_kallsyms; } ;
struct TYPE_9__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_8__ {int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_7__ {scalar_t__ st_shndx; int st_name; unsigned long st_value; } ;
typedef  TYPE_2__ Elf_Sym ;
typedef  TYPE_3__ Elf_Shdr ;
typedef  TYPE_4__ Elf_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ELF_R_SYM (int /*<<< orphan*/ ) ; 
 int KSYM_NAME_LEN ; 
 int MODULE_NAME_LEN ; 
 scalar_t__ SHN_LIVEPATCH ; 
 int klp_find_object_symbol (char*,char*,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int sscanf (char*,char*,char*,char*,unsigned long*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int klp_resolve_symbols(Elf_Shdr *relasec, struct module *pmod)
{
	int i, cnt, vmlinux, ret;
	char objname[MODULE_NAME_LEN];
	char symname[KSYM_NAME_LEN];
	char *strtab = pmod->core_kallsyms.strtab;
	Elf_Rela *relas;
	Elf_Sym *sym;
	unsigned long sympos, addr;

	/*
	 * Since the field widths for objname and symname in the sscanf()
	 * call are hard-coded and correspond to MODULE_NAME_LEN and
	 * KSYM_NAME_LEN respectively, we must make sure that MODULE_NAME_LEN
	 * and KSYM_NAME_LEN have the values we expect them to have.
	 *
	 * Because the value of MODULE_NAME_LEN can differ among architectures,
	 * we use the smallest/strictest upper bound possible (56, based on
	 * the current definition of MODULE_NAME_LEN) to prevent overflows.
	 */
	BUILD_BUG_ON(MODULE_NAME_LEN < 56 || KSYM_NAME_LEN != 128);

	relas = (Elf_Rela *) relasec->sh_addr;
	/* For each rela in this klp relocation section */
	for (i = 0; i < relasec->sh_size / sizeof(Elf_Rela); i++) {
		sym = pmod->core_kallsyms.symtab + ELF_R_SYM(relas[i].r_info);
		if (sym->st_shndx != SHN_LIVEPATCH) {
			pr_err("symbol %s is not marked as a livepatch symbol\n",
			       strtab + sym->st_name);
			return -EINVAL;
		}

		/* Format: .klp.sym.objname.symname,sympos */
		cnt = sscanf(strtab + sym->st_name,
			     ".klp.sym.%55[^.].%127[^,],%lu",
			     objname, symname, &sympos);
		if (cnt != 3) {
			pr_err("symbol %s has an incorrectly formatted name\n",
			       strtab + sym->st_name);
			return -EINVAL;
		}

		/* klp_find_object_symbol() treats a NULL objname as vmlinux */
		vmlinux = !strcmp(objname, "vmlinux");
		ret = klp_find_object_symbol(vmlinux ? NULL : objname,
					     symname, sympos, &addr);
		if (ret)
			return ret;

		sym->st_value = addr;
	}

	return 0;
}