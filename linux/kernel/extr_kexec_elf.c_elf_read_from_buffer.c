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
struct kexec_elf_info {char const* buffer; struct elfhdr* ehdr; } ;
struct elfhdr {scalar_t__ e_phoff; scalar_t__ e_phnum; } ;

/* Variables and functions */
 int elf_read_ehdr (char const*,size_t,struct elfhdr*) ; 
 int elf_read_phdrs (char const*,size_t,struct kexec_elf_info*) ; 

__attribute__((used)) static int elf_read_from_buffer(const char *buf, size_t len,
				struct elfhdr *ehdr,
				struct kexec_elf_info *elf_info)
{
	int ret;

	ret = elf_read_ehdr(buf, len, ehdr);
	if (ret)
		return ret;

	elf_info->buffer = buf;
	elf_info->ehdr = ehdr;
	if (ehdr->e_phoff > 0 && ehdr->e_phnum > 0) {
		ret = elf_read_phdrs(buf, len, elf_info);
		if (ret)
			return ret;
	}
	return 0;
}