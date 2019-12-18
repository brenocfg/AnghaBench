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
struct kexec_elf_info {int dummy; } ;
struct elfhdr {int dummy; } ;

/* Variables and functions */
 int ENOEXEC ; 
 scalar_t__ elf_check_arch (struct elfhdr*) ; 
 int kexec_build_elf_info (char const*,unsigned long,struct elfhdr*,struct kexec_elf_info*) ; 
 int /*<<< orphan*/  kexec_free_elf_info (struct kexec_elf_info*) ; 

int kexec_elf_probe(const char *buf, unsigned long len)
{
	struct elfhdr ehdr;
	struct kexec_elf_info elf_info;
	int ret;

	ret = kexec_build_elf_info(buf, len, &ehdr, &elf_info);
	if (ret)
		return ret;

	kexec_free_elf_info(&elf_info);

	return elf_check_arch(&ehdr) ? 0 : -ENOEXEC;
}