#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct elf_info {size_t num_sections; TYPE_1__* sechdrs; scalar_t__ hdr; } ;
struct devtable {char* device_id; int /*<<< orphan*/  do_entry; int /*<<< orphan*/  id_size; } ;
struct TYPE_6__ {int st_value; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_shndx; } ;
struct TYPE_5__ {int sh_type; int sh_offset; } ;
typedef  TYPE_2__ Elf_Sym ;

/* Variables and functions */
 int ARRAY_SIZE (struct devtable*) ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int SHT_NOBITS ; 
 scalar_t__ STT_OBJECT ; 
 char* calloc (int,int /*<<< orphan*/ ) ; 
 struct devtable* devtable ; 
 int /*<<< orphan*/  do_of_table (void*,int /*<<< orphan*/ ,struct module*) ; 
 int /*<<< orphan*/  do_pnp_card_entries (void*,int /*<<< orphan*/ ,struct module*) ; 
 int /*<<< orphan*/  do_pnp_device_entry (void*,int /*<<< orphan*/ ,struct module*) ; 
 int /*<<< orphan*/  do_table (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct module*) ; 
 int /*<<< orphan*/  do_usb_table (void*,int /*<<< orphan*/ ,struct module*) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t get_secindex (struct elf_info*,TYPE_2__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 
 scalar_t__ sym_is (char const*,unsigned int,char*) ; 

void handle_moddevtable(struct module *mod, struct elf_info *info,
			Elf_Sym *sym, const char *symname)
{
	void *symval;
	char *zeros = NULL;
	const char *name, *identifier;
	unsigned int namelen;

	/* We're looking for a section relative symbol */
	if (!sym->st_shndx || get_secindex(info, sym) >= info->num_sections)
		return;

	/* We're looking for an object */
	if (ELF_ST_TYPE(sym->st_info) != STT_OBJECT)
		return;

	/* All our symbols are of form __mod_<name>__<identifier>_device_table. */
	if (strncmp(symname, "__mod_", strlen("__mod_")))
		return;
	name = symname + strlen("__mod_");
	namelen = strlen(name);
	if (namelen < strlen("_device_table"))
		return;
	if (strcmp(name + namelen - strlen("_device_table"), "_device_table"))
		return;
	identifier = strstr(name, "__");
	if (!identifier)
		return;
	namelen = identifier - name;

	/* Handle all-NULL symbols allocated into .bss */
	if (info->sechdrs[get_secindex(info, sym)].sh_type & SHT_NOBITS) {
		zeros = calloc(1, sym->st_size);
		symval = zeros;
	} else {
		symval = (void *)info->hdr
			+ info->sechdrs[get_secindex(info, sym)].sh_offset
			+ sym->st_value;
	}

	/* First handle the "special" cases */
	if (sym_is(name, namelen, "usb"))
		do_usb_table(symval, sym->st_size, mod);
	if (sym_is(name, namelen, "of"))
		do_of_table(symval, sym->st_size, mod);
	else if (sym_is(name, namelen, "pnp"))
		do_pnp_device_entry(symval, sym->st_size, mod);
	else if (sym_is(name, namelen, "pnp_card"))
		do_pnp_card_entries(symval, sym->st_size, mod);
	else {
		int i;

		for (i = 0; i < ARRAY_SIZE(devtable); i++) {
			const struct devtable *p = &devtable[i];

			if (sym_is(name, namelen, p->device_id)) {
				do_table(symval, sym->st_size, p->id_size,
					 p->device_id, p->do_entry, mod);
				break;
			}
		}
	}
	free(zeros);
}