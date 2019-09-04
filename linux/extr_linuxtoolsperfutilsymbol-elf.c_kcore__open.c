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
struct kcore {int fd; scalar_t__ elfclass; int /*<<< orphan*/  elf; int /*<<< orphan*/  ehdr; } ;
typedef  int /*<<< orphan*/  GElf_Ehdr ;

/* Variables and functions */
 scalar_t__ ELFCLASSNONE ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ ) ; 
 scalar_t__ gelf_getclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kcore__open(struct kcore *kcore, const char *filename)
{
	GElf_Ehdr *ehdr;

	kcore->fd = open(filename, O_RDONLY);
	if (kcore->fd == -1)
		return -1;

	kcore->elf = elf_begin(kcore->fd, ELF_C_READ, NULL);
	if (!kcore->elf)
		goto out_close;

	kcore->elfclass = gelf_getclass(kcore->elf);
	if (kcore->elfclass == ELFCLASSNONE)
		goto out_end;

	ehdr = gelf_getehdr(kcore->elf, &kcore->ehdr);
	if (!ehdr)
		goto out_end;

	return 0;

out_end:
	elf_end(kcore->elf);
out_close:
	close(kcore->fd);
	return -1;
}