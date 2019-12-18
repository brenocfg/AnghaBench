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
struct kcore {int elfclass; int fd; int /*<<< orphan*/  elf; int /*<<< orphan*/  ehdr; } ;
typedef  int /*<<< orphan*/  GElf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_newehdr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mkstemp (char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int kcore__init(struct kcore *kcore, char *filename, int elfclass,
		       bool temp)
{
	kcore->elfclass = elfclass;

	if (temp)
		kcore->fd = mkstemp(filename);
	else
		kcore->fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0400);
	if (kcore->fd == -1)
		return -1;

	kcore->elf = elf_begin(kcore->fd, ELF_C_WRITE, NULL);
	if (!kcore->elf)
		goto out_close;

	if (!gelf_newehdr(kcore->elf, elfclass))
		goto out_end;

	memset(&kcore->ehdr, 0, sizeof(GElf_Ehdr));

	return 0;

out_end:
	elf_end(kcore->elf);
out_close:
	close(kcore->fd);
	unlink(filename);
	return -1;
}