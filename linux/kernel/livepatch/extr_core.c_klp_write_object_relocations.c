#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  strtab; } ;
struct module {TYPE_3__* klp_info; TYPE_2__ core_kallsyms; } ;
struct klp_object {char* name; } ;
struct TYPE_10__ {int sh_name; int sh_flags; } ;
struct TYPE_7__ {int e_shnum; } ;
struct TYPE_9__ {char* secstrings; int /*<<< orphan*/  symndx; TYPE_4__* sechdrs; TYPE_1__ hdr; } ;
typedef  TYPE_4__ Elf_Shdr ;

/* Variables and functions */
 int EINVAL ; 
 int MODULE_NAME_LEN ; 
 int SHF_RELA_LIVEPATCH ; 
 scalar_t__ WARN_ON (int) ; 
 int apply_relocate_add (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct module*) ; 
 scalar_t__ klp_is_module (struct klp_object*) ; 
 int /*<<< orphan*/  klp_is_object_loaded (struct klp_object*) ; 
 int klp_resolve_symbols (TYPE_4__*,struct module*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int sscanf (char const*,char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int klp_write_object_relocations(struct module *pmod,
					struct klp_object *obj)
{
	int i, cnt, ret = 0;
	const char *objname, *secname;
	char sec_objname[MODULE_NAME_LEN];
	Elf_Shdr *sec;

	if (WARN_ON(!klp_is_object_loaded(obj)))
		return -EINVAL;

	objname = klp_is_module(obj) ? obj->name : "vmlinux";

	/* For each klp relocation section */
	for (i = 1; i < pmod->klp_info->hdr.e_shnum; i++) {
		sec = pmod->klp_info->sechdrs + i;
		secname = pmod->klp_info->secstrings + sec->sh_name;
		if (!(sec->sh_flags & SHF_RELA_LIVEPATCH))
			continue;

		/*
		 * Format: .klp.rela.sec_objname.section_name
		 * See comment in klp_resolve_symbols() for an explanation
		 * of the selected field width value.
		 */
		cnt = sscanf(secname, ".klp.rela.%55[^.]", sec_objname);
		if (cnt != 1) {
			pr_err("section %s has an incorrectly formatted name\n",
			       secname);
			ret = -EINVAL;
			break;
		}

		if (strcmp(objname, sec_objname))
			continue;

		ret = klp_resolve_symbols(sec, pmod);
		if (ret)
			break;

		ret = apply_relocate_add(pmod->klp_info->sechdrs,
					 pmod->core_kallsyms.strtab,
					 pmod->klp_info->symndx, i, pmod);
		if (ret)
			break;
	}

	return ret;
}