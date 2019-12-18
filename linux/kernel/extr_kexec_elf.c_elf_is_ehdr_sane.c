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
struct elfhdr {int e_phnum; int e_phentsize; int e_shnum; int e_shentsize; scalar_t__* e_ident; scalar_t__ e_version; size_t e_phoff; size_t e_shoff; } ;
struct elf_shdr {int dummy; } ;
struct elf_phdr {int dummy; } ;

/* Variables and functions */
 size_t EI_VERSION ; 
 scalar_t__ EV_CURRENT ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static bool elf_is_ehdr_sane(const struct elfhdr *ehdr, size_t buf_len)
{
	if (ehdr->e_phnum > 0 && ehdr->e_phentsize != sizeof(struct elf_phdr)) {
		pr_debug("Bad program header size.\n");
		return false;
	} else if (ehdr->e_shnum > 0 &&
		   ehdr->e_shentsize != sizeof(struct elf_shdr)) {
		pr_debug("Bad section header size.\n");
		return false;
	} else if (ehdr->e_ident[EI_VERSION] != EV_CURRENT ||
		   ehdr->e_version != EV_CURRENT) {
		pr_debug("Unknown ELF version.\n");
		return false;
	}

	if (ehdr->e_phoff > 0 && ehdr->e_phnum > 0) {
		size_t phdr_size;

		/*
		 * e_phnum is at most 65535 so calculating the size of the
		 * program header cannot overflow.
		 */
		phdr_size = sizeof(struct elf_phdr) * ehdr->e_phnum;

		/* Sanity check the program header table location. */
		if (ehdr->e_phoff + phdr_size < ehdr->e_phoff) {
			pr_debug("Program headers at invalid location.\n");
			return false;
		} else if (ehdr->e_phoff + phdr_size > buf_len) {
			pr_debug("Program headers truncated.\n");
			return false;
		}
	}

	if (ehdr->e_shoff > 0 && ehdr->e_shnum > 0) {
		size_t shdr_size;

		/*
		 * e_shnum is at most 65536 so calculating
		 * the size of the section header cannot overflow.
		 */
		shdr_size = sizeof(struct elf_shdr) * ehdr->e_shnum;

		/* Sanity check the section header table location. */
		if (ehdr->e_shoff + shdr_size < ehdr->e_shoff) {
			pr_debug("Section headers at invalid location.\n");
			return false;
		} else if (ehdr->e_shoff + shdr_size > buf_len) {
			pr_debug("Section headers truncated.\n");
			return false;
		}
	}

	return true;
}