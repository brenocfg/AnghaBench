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
struct TYPE_6__ {size_t sh_size; size_t sh_entsize; int sh_addralign; size_t sh_name; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; } ;
struct section {size_t len; int changed; TYPE_3__ sh; scalar_t__ name; int /*<<< orphan*/  idx; TYPE_1__* data; int /*<<< orphan*/  list; int /*<<< orphan*/  symbol_hash; int /*<<< orphan*/  rela_hash; int /*<<< orphan*/  rela_list; int /*<<< orphan*/  symbol_list; } ;
struct elf {int /*<<< orphan*/  elf; int /*<<< orphan*/  sections; } ;
struct TYPE_5__ {int d_align; scalar_t__ d_size; scalar_t__ d_buf; } ;
struct TYPE_4__ {size_t d_size; int d_align; struct section* d_buf; } ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_2__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHF_ALLOC ; 
 int /*<<< orphan*/  SHT_PROGBITS ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WARN_ELF (char*) ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_ndxscn (int /*<<< orphan*/ *) ; 
 void* elf_newdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_newscn (int /*<<< orphan*/ ) ; 
 struct section* find_section_by_name (struct elf*,char*) ; 
 int /*<<< orphan*/  gelf_getshdr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct section*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 

struct section *elf_create_section(struct elf *elf, const char *name,
				   size_t entsize, int nr)
{
	struct section *sec, *shstrtab;
	size_t size = entsize * nr;
	Elf_Scn *s;
	Elf_Data *data;

	sec = malloc(sizeof(*sec));
	if (!sec) {
		perror("malloc");
		return NULL;
	}
	memset(sec, 0, sizeof(*sec));

	INIT_LIST_HEAD(&sec->symbol_list);
	INIT_LIST_HEAD(&sec->rela_list);
	hash_init(sec->rela_hash);
	hash_init(sec->symbol_hash);

	list_add_tail(&sec->list, &elf->sections);

	s = elf_newscn(elf->elf);
	if (!s) {
		WARN_ELF("elf_newscn");
		return NULL;
	}

	sec->name = strdup(name);
	if (!sec->name) {
		perror("strdup");
		return NULL;
	}

	sec->idx = elf_ndxscn(s);
	sec->len = size;
	sec->changed = true;

	sec->data = elf_newdata(s);
	if (!sec->data) {
		WARN_ELF("elf_newdata");
		return NULL;
	}

	sec->data->d_size = size;
	sec->data->d_align = 1;

	if (size) {
		sec->data->d_buf = malloc(size);
		if (!sec->data->d_buf) {
			perror("malloc");
			return NULL;
		}
		memset(sec->data->d_buf, 0, size);
	}

	if (!gelf_getshdr(s, &sec->sh)) {
		WARN_ELF("gelf_getshdr");
		return NULL;
	}

	sec->sh.sh_size = size;
	sec->sh.sh_entsize = entsize;
	sec->sh.sh_type = SHT_PROGBITS;
	sec->sh.sh_addralign = 1;
	sec->sh.sh_flags = SHF_ALLOC;


	/* Add section name to .shstrtab (or .strtab for Clang) */
	shstrtab = find_section_by_name(elf, ".shstrtab");
	if (!shstrtab)
		shstrtab = find_section_by_name(elf, ".strtab");
	if (!shstrtab) {
		WARN("can't find .shstrtab or .strtab section");
		return NULL;
	}

	s = elf_getscn(elf->elf, shstrtab->idx);
	if (!s) {
		WARN_ELF("elf_getscn");
		return NULL;
	}

	data = elf_newdata(s);
	if (!data) {
		WARN_ELF("elf_newdata");
		return NULL;
	}

	data->d_buf = sec->name;
	data->d_size = strlen(name) + 1;
	data->d_align = 1;

	sec->sh.sh_name = shstrtab->len;

	shstrtab->len += strlen(name) + 1;
	shstrtab->changed = true;

	return sec;
}