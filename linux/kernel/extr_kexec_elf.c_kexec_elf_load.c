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
struct kimage {int dummy; } ;
struct kexec_elf_info {scalar_t__ buffer; struct elf_phdr* proghdrs; } ;
struct kexec_buf {size_t bufsz; size_t memsz; unsigned long mem; int /*<<< orphan*/  buf_min; int /*<<< orphan*/  buf_align; void* buffer; } ;
struct elfhdr {size_t e_phnum; } ;
struct elf_phdr {scalar_t__ p_type; size_t p_filesz; size_t p_memsz; int p_offset; int /*<<< orphan*/  p_paddr; int /*<<< orphan*/  p_align; } ;

/* Variables and functions */
 unsigned long KEXEC_BUF_MEM_UNKNOWN ; 
 scalar_t__ PT_LOAD ; 
 unsigned long UINT_MAX ; 
 int kexec_add_buffer (struct kexec_buf*) ; 

int kexec_elf_load(struct kimage *image, struct elfhdr *ehdr,
			 struct kexec_elf_info *elf_info,
			 struct kexec_buf *kbuf,
			 unsigned long *lowest_load_addr)
{
	unsigned long lowest_addr = UINT_MAX;
	int ret;
	size_t i;

	/* Read in the PT_LOAD segments. */
	for (i = 0; i < ehdr->e_phnum; i++) {
		unsigned long load_addr;
		size_t size;
		const struct elf_phdr *phdr;

		phdr = &elf_info->proghdrs[i];
		if (phdr->p_type != PT_LOAD)
			continue;

		size = phdr->p_filesz;
		if (size > phdr->p_memsz)
			size = phdr->p_memsz;

		kbuf->buffer = (void *) elf_info->buffer + phdr->p_offset;
		kbuf->bufsz = size;
		kbuf->memsz = phdr->p_memsz;
		kbuf->buf_align = phdr->p_align;
		kbuf->buf_min = phdr->p_paddr;
		kbuf->mem = KEXEC_BUF_MEM_UNKNOWN;
		ret = kexec_add_buffer(kbuf);
		if (ret)
			goto out;
		load_addr = kbuf->mem;

		if (load_addr < lowest_addr)
			lowest_addr = load_addr;
	}

	*lowest_load_addr = lowest_addr;
	ret = 0;
 out:
	return ret;
}