#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sh_addralign; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_link; int /*<<< orphan*/  sh_type; } ;
struct section {char* name; TYPE_1__ sh; int /*<<< orphan*/  idx; struct section* base; struct section* rela; } ;
struct elf {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  idx; } ;
typedef  int /*<<< orphan*/  GElf_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  SHF_INFO_LINK ; 
 int /*<<< orphan*/  SHT_RELA ; 
 struct section* elf_create_section (struct elf*,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* find_section_by_name (struct elf*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

struct section *elf_create_rela_section(struct elf *elf, struct section *base)
{
	char *relaname;
	struct section *sec;

	relaname = malloc(strlen(base->name) + strlen(".rela") + 1);
	if (!relaname) {
		perror("malloc");
		return NULL;
	}
	strcpy(relaname, ".rela");
	strcat(relaname, base->name);

	sec = elf_create_section(elf, relaname, sizeof(GElf_Rela), 0);
	free(relaname);
	if (!sec)
		return NULL;

	base->rela = sec;
	sec->base = base;

	sec->sh.sh_type = SHT_RELA;
	sec->sh.sh_addralign = 8;
	sec->sh.sh_link = find_section_by_name(elf, ".symtab")->idx;
	sec->sh.sh_info = base->idx;
	sec->sh.sh_flags = SHF_INFO_LINK;

	return sec;
}