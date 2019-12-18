#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elf {int fd; int /*<<< orphan*/  ehdr; int /*<<< orphan*/  elf; int /*<<< orphan*/  sections; } ;
typedef  int /*<<< orphan*/  Elf_Cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_RDWR ; 
 int /*<<< orphan*/  ELF_C_READ_MMAP ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  WARN_ELF (char*) ; 
 int /*<<< orphan*/  elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_close (struct elf*) ; 
 int /*<<< orphan*/  elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  gelf_getehdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct elf* malloc (int) ; 
 int /*<<< orphan*/  memset (struct elf*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ read_relas (struct elf*) ; 
 scalar_t__ read_sections (struct elf*) ; 
 scalar_t__ read_symbols (struct elf*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

struct elf *elf_read(const char *name, int flags)
{
	struct elf *elf;
	Elf_Cmd cmd;

	elf_version(EV_CURRENT);

	elf = malloc(sizeof(*elf));
	if (!elf) {
		perror("malloc");
		return NULL;
	}
	memset(elf, 0, sizeof(*elf));

	INIT_LIST_HEAD(&elf->sections);

	elf->fd = open(name, flags);
	if (elf->fd == -1) {
		fprintf(stderr, "objtool: Can't open '%s': %s\n",
			name, strerror(errno));
		goto err;
	}

	if ((flags & O_ACCMODE) == O_RDONLY)
		cmd = ELF_C_READ_MMAP;
	else if ((flags & O_ACCMODE) == O_RDWR)
		cmd = ELF_C_RDWR;
	else /* O_WRONLY */
		cmd = ELF_C_WRITE;

	elf->elf = elf_begin(elf->fd, cmd, NULL);
	if (!elf->elf) {
		WARN_ELF("elf_begin");
		goto err;
	}

	if (!gelf_getehdr(elf->elf, &elf->ehdr)) {
		WARN_ELF("gelf_getehdr");
		goto err;
	}

	if (read_sections(elf))
		goto err;

	if (read_symbols(elf))
		goto err;

	if (read_relas(elf))
		goto err;

	return elf;

err:
	elf_close(elf);
	return NULL;
}