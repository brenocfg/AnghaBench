#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  e_shstrndx; } ;
struct TYPE_6__ {int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  TYPE_2__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  BTF_ELF_SEC ; 
 scalar_t__ CHECK (int,char*,...) ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_errno () ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  gelf_getehdr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int file_has_btf_elf(const char *fn)
{
	Elf_Scn *scn = NULL;
	GElf_Ehdr ehdr;
	int elf_fd;
	Elf *elf;
	int ret;

	if (CHECK(elf_version(EV_CURRENT) == EV_NONE,
		  "elf_version(EV_CURRENT) == EV_NONE"))
		return -1;

	elf_fd = open(fn, O_RDONLY);
	if (CHECK(elf_fd == -1, "open(%s): errno:%d", fn, errno))
		return -1;

	elf = elf_begin(elf_fd, ELF_C_READ, NULL);
	if (CHECK(!elf, "elf_begin(%s): %s", fn, elf_errmsg(elf_errno()))) {
		ret = -1;
		goto done;
	}

	if (CHECK(!gelf_getehdr(elf, &ehdr), "!gelf_getehdr(%s)", fn)) {
		ret = -1;
		goto done;
	}

	while ((scn = elf_nextscn(elf, scn))) {
		const char *sh_name;
		GElf_Shdr sh;

		if (CHECK(gelf_getshdr(scn, &sh) != &sh,
			  "file:%s gelf_getshdr != &sh", fn)) {
			ret = -1;
			goto done;
		}

		sh_name = elf_strptr(elf, ehdr.e_shstrndx, sh.sh_name);
		if (!strcmp(sh_name, BTF_ELF_SEC)) {
			ret = 1;
			goto done;
		}
	}

	ret = 0;

done:
	close(elf_fd);
	elf_end(elf);
	return ret;
}