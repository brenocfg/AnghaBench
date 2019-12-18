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
struct TYPE_3__ {scalar_t__ sh_size; int /*<<< orphan*/  sh_name; } ;
struct section {scalar_t__ len; TYPE_1__ sh; int /*<<< orphan*/  name; TYPE_2__* data; int /*<<< orphan*/  idx; int /*<<< orphan*/  list; int /*<<< orphan*/  symbol_hash; int /*<<< orphan*/  rela_hash; int /*<<< orphan*/  rela_list; int /*<<< orphan*/  symbol_list; } ;
struct elf {int /*<<< orphan*/  elf; int /*<<< orphan*/  sections; } ;
struct TYPE_4__ {scalar_t__ d_off; scalar_t__ d_size; } ;
typedef  int /*<<< orphan*/  Elf_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  WARN_ELF (char*) ; 
 TYPE_2__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ ,int) ; 
 scalar_t__ elf_getshdrnum (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ elf_getshdrstrndx (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  elf_ndxscn (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_nextscn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_strptr (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct section* malloc (int) ; 
 int /*<<< orphan*/  memset (struct section*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int read_sections(struct elf *elf)
{
	Elf_Scn *s = NULL;
	struct section *sec;
	size_t shstrndx, sections_nr;
	int i;

	if (elf_getshdrnum(elf->elf, &sections_nr)) {
		WARN_ELF("elf_getshdrnum");
		return -1;
	}

	if (elf_getshdrstrndx(elf->elf, &shstrndx)) {
		WARN_ELF("elf_getshdrstrndx");
		return -1;
	}

	for (i = 0; i < sections_nr; i++) {
		sec = malloc(sizeof(*sec));
		if (!sec) {
			perror("malloc");
			return -1;
		}
		memset(sec, 0, sizeof(*sec));

		INIT_LIST_HEAD(&sec->symbol_list);
		INIT_LIST_HEAD(&sec->rela_list);
		hash_init(sec->rela_hash);
		hash_init(sec->symbol_hash);

		list_add_tail(&sec->list, &elf->sections);

		s = elf_getscn(elf->elf, i);
		if (!s) {
			WARN_ELF("elf_getscn");
			return -1;
		}

		sec->idx = elf_ndxscn(s);

		if (!gelf_getshdr(s, &sec->sh)) {
			WARN_ELF("gelf_getshdr");
			return -1;
		}

		sec->name = elf_strptr(elf->elf, shstrndx, sec->sh.sh_name);
		if (!sec->name) {
			WARN_ELF("elf_strptr");
			return -1;
		}

		if (sec->sh.sh_size != 0) {
			sec->data = elf_getdata(s, NULL);
			if (!sec->data) {
				WARN_ELF("elf_getdata");
				return -1;
			}
			if (sec->data->d_off != 0 ||
			    sec->data->d_size != sec->sh.sh_size) {
				WARN("unexpected data attributes for %s",
				     sec->name);
				return -1;
			}
		}
		sec->len = sec->sh.sh_size;
	}

	/* sanity check, one more call to elf_nextscn() should return NULL */
	if (elf_nextscn(elf->elf, s)) {
		WARN("section entry mismatch");
		return -1;
	}

	return 0;
}