#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct module {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {size_t sym; int pcpu; } ;
struct load_info {char* strtab; TYPE_3__* sechdrs; TYPE_1__ index; } ;
struct kernel_symbol {int dummy; } ;
struct TYPE_6__ {unsigned long sh_addr; int sh_size; } ;
struct TYPE_5__ {int st_name; int st_shndx; unsigned long st_value; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_2__ Elf_Sym ;
typedef  TYPE_3__ Elf_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int ENOEXEC ; 
 int /*<<< orphan*/  IS_ERR (struct kernel_symbol const*) ; 
 int /*<<< orphan*/  PTR_ERR (struct kernel_symbol const*) ; 
#define  SHN_ABS 131 
#define  SHN_COMMON 130 
#define  SHN_LIVEPATCH 129 
#define  SHN_UNDEF 128 
 int /*<<< orphan*/  STB_WEAK ; 
 unsigned long kernel_symbol_value (struct kernel_symbol const*) ; 
 scalar_t__ mod_percpu (struct module*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 struct kernel_symbol* resolve_symbol_wait (struct module*,struct load_info const*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int simplify_symbols(struct module *mod, const struct load_info *info)
{
	Elf_Shdr *symsec = &info->sechdrs[info->index.sym];
	Elf_Sym *sym = (void *)symsec->sh_addr;
	unsigned long secbase;
	unsigned int i;
	int ret = 0;
	const struct kernel_symbol *ksym;

	for (i = 1; i < symsec->sh_size / sizeof(Elf_Sym); i++) {
		const char *name = info->strtab + sym[i].st_name;

		switch (sym[i].st_shndx) {
		case SHN_COMMON:
			/* Ignore common symbols */
			if (!strncmp(name, "__gnu_lto", 9))
				break;

			/* We compiled with -fno-common.  These are not
			   supposed to happen.  */
			pr_debug("Common symbol: %s\n", name);
			pr_warn("%s: please compile with -fno-common\n",
			       mod->name);
			ret = -ENOEXEC;
			break;

		case SHN_ABS:
			/* Don't need to do anything */
			pr_debug("Absolute symbol: 0x%08lx\n",
			       (long)sym[i].st_value);
			break;

		case SHN_LIVEPATCH:
			/* Livepatch symbols are resolved by livepatch */
			break;

		case SHN_UNDEF:
			ksym = resolve_symbol_wait(mod, info, name);
			/* Ok if resolved.  */
			if (ksym && !IS_ERR(ksym)) {
				sym[i].st_value = kernel_symbol_value(ksym);
				break;
			}

			/* Ok if weak.  */
			if (!ksym && ELF_ST_BIND(sym[i].st_info) == STB_WEAK)
				break;

			ret = PTR_ERR(ksym) ?: -ENOENT;
			pr_warn("%s: Unknown symbol %s (err %d)\n",
				mod->name, name, ret);
			break;

		default:
			/* Divert to percpu allocation if a percpu var. */
			if (sym[i].st_shndx == info->index.pcpu)
				secbase = (unsigned long)mod_percpu(mod);
			else
				secbase = info->sechdrs[sym[i].st_shndx].sh_addr;
			sym[i].st_value += secbase;
			break;
		}
	}

	return ret;
}