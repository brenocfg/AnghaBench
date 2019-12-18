#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kexec_elf_info {TYPE_1__* proghdrs; } ;
struct elfhdr {scalar_t__ e_type; int e_phnum; } ;
struct TYPE_2__ {scalar_t__ p_type; } ;

/* Variables and functions */
 int ENOEXEC ; 
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ PT_INTERP ; 
 int elf_read_from_buffer (char const*,size_t,struct elfhdr*,struct kexec_elf_info*) ; 
 int /*<<< orphan*/  kexec_free_elf_info (struct kexec_elf_info*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int kexec_build_elf_info(const char *buf, size_t len, struct elfhdr *ehdr,
			       struct kexec_elf_info *elf_info)
{
	int i;
	int ret;

	ret = elf_read_from_buffer(buf, len, ehdr, elf_info);
	if (ret)
		return ret;

	/* Big endian vmlinux has type ET_DYN. */
	if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN) {
		pr_err("Not an ELF executable.\n");
		goto error;
	} else if (!elf_info->proghdrs) {
		pr_err("No ELF program header.\n");
		goto error;
	}

	for (i = 0; i < ehdr->e_phnum; i++) {
		/*
		 * Kexec does not support loading interpreters.
		 * In addition this check keeps us from attempting
		 * to kexec ordinay executables.
		 */
		if (elf_info->proghdrs[i].p_type == PT_INTERP) {
			pr_err("Requires an ELF interpreter.\n");
			goto error;
		}
	}

	return 0;
error:
	kexec_free_elf_info(elf_info);
	return -ENOEXEC;
}