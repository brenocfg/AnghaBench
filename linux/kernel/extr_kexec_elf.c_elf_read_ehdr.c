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
struct elfhdr {int* e_ident; int e_ehsize; int e_type; int e_machine; int e_phentsize; int e_phnum; int e_shentsize; int e_shnum; int e_shstrndx; void* e_shoff; void* e_phoff; void* e_entry; void* e_flags; void* e_version; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
#define  ELFCLASS32 129 
#define  ELFCLASS64 128 
 int ELFDATA2LSB ; 
 int ELFDATA2MSB ; 
 int ELF_CLASS ; 
 int ENOEXEC ; 
 int elf16_to_cpu (struct elfhdr*,int) ; 
 void* elf32_to_cpu (struct elfhdr*,void*) ; 
 void* elf64_to_cpu (struct elfhdr*,void*) ; 
 scalar_t__ elf_is_ehdr_sane (struct elfhdr*,size_t) ; 
 int /*<<< orphan*/  elf_is_elf_file (struct elfhdr*) ; 
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct elfhdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int elf_read_ehdr(const char *buf, size_t len, struct elfhdr *ehdr)
{
	struct elfhdr *buf_ehdr;

	if (len < sizeof(*buf_ehdr)) {
		pr_debug("Buffer is too small to hold ELF header.\n");
		return -ENOEXEC;
	}

	memset(ehdr, 0, sizeof(*ehdr));
	memcpy(ehdr->e_ident, buf, sizeof(ehdr->e_ident));
	if (!elf_is_elf_file(ehdr)) {
		pr_debug("No ELF header magic.\n");
		return -ENOEXEC;
	}

	if (ehdr->e_ident[EI_CLASS] != ELF_CLASS) {
		pr_debug("Not a supported ELF class.\n");
		return -ENOEXEC;
	} else  if (ehdr->e_ident[EI_DATA] != ELFDATA2LSB &&
		ehdr->e_ident[EI_DATA] != ELFDATA2MSB) {
		pr_debug("Not a supported ELF data format.\n");
		return -ENOEXEC;
	}

	buf_ehdr = (struct elfhdr *) buf;
	if (elf16_to_cpu(ehdr, buf_ehdr->e_ehsize) != sizeof(*buf_ehdr)) {
		pr_debug("Bad ELF header size.\n");
		return -ENOEXEC;
	}

	ehdr->e_type      = elf16_to_cpu(ehdr, buf_ehdr->e_type);
	ehdr->e_machine   = elf16_to_cpu(ehdr, buf_ehdr->e_machine);
	ehdr->e_version   = elf32_to_cpu(ehdr, buf_ehdr->e_version);
	ehdr->e_flags     = elf32_to_cpu(ehdr, buf_ehdr->e_flags);
	ehdr->e_phentsize = elf16_to_cpu(ehdr, buf_ehdr->e_phentsize);
	ehdr->e_phnum     = elf16_to_cpu(ehdr, buf_ehdr->e_phnum);
	ehdr->e_shentsize = elf16_to_cpu(ehdr, buf_ehdr->e_shentsize);
	ehdr->e_shnum     = elf16_to_cpu(ehdr, buf_ehdr->e_shnum);
	ehdr->e_shstrndx  = elf16_to_cpu(ehdr, buf_ehdr->e_shstrndx);

	switch (ehdr->e_ident[EI_CLASS]) {
	case ELFCLASS64:
		ehdr->e_entry = elf64_to_cpu(ehdr, buf_ehdr->e_entry);
		ehdr->e_phoff = elf64_to_cpu(ehdr, buf_ehdr->e_phoff);
		ehdr->e_shoff = elf64_to_cpu(ehdr, buf_ehdr->e_shoff);
		break;

	case ELFCLASS32:
		ehdr->e_entry = elf32_to_cpu(ehdr, buf_ehdr->e_entry);
		ehdr->e_phoff = elf32_to_cpu(ehdr, buf_ehdr->e_phoff);
		ehdr->e_shoff = elf32_to_cpu(ehdr, buf_ehdr->e_shoff);
		break;

	default:
		pr_debug("Unknown ELF class.\n");
		return -EINVAL;
	}

	return elf_is_ehdr_sane(ehdr, len) ? 0 : -ENOEXEC;
}