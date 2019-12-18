#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {unsigned long start_code; unsigned long end_code; unsigned long start_data; unsigned long end_data; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int e_phnum; } ;
struct elf_fdpic_params {unsigned long load_addr; int flags; unsigned long elfhdr_addr; struct elf32_phdr* phdrs; TYPE_2__ hdr; TYPE_1__* loadmap; } ;
struct elf32_phdr {scalar_t__ p_type; unsigned long p_vaddr; unsigned long p_memsz; scalar_t__ p_offset; unsigned long p_filesz; int p_flags; } ;
struct elf32_fdpic_loadseg {unsigned long addr; unsigned long p_vaddr; unsigned long p_memsz; } ;
struct TYPE_3__ {struct elf32_fdpic_loadseg* segs; } ;

/* Variables and functions */
 int EFAULT ; 
 int ELF_FDPIC_FLAG_EXECUTABLE ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 unsigned long MAP_EXECUTABLE ; 
 unsigned long MAP_PRIVATE ; 
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 int PF_X ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ PT_LOAD ; 
 unsigned long ULONG_MAX ; 
 scalar_t__ clear_user (void*,unsigned long) ; 
 int read_code (struct file*,unsigned long,scalar_t__,unsigned long) ; 
 unsigned long vm_mmap (int /*<<< orphan*/ *,unsigned long,unsigned long,int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elf_fdpic_map_file_constdisp_on_uclinux(
	struct elf_fdpic_params *params,
	struct file *file,
	struct mm_struct *mm)
{
	struct elf32_fdpic_loadseg *seg;
	struct elf32_phdr *phdr;
	unsigned long load_addr, base = ULONG_MAX, top = 0, maddr = 0, mflags;
	int loop, ret;

	load_addr = params->load_addr;
	seg = params->loadmap->segs;

	/* determine the bounds of the contiguous overall allocation we must
	 * make */
	phdr = params->phdrs;
	for (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) {
		if (params->phdrs[loop].p_type != PT_LOAD)
			continue;

		if (base > phdr->p_vaddr)
			base = phdr->p_vaddr;
		if (top < phdr->p_vaddr + phdr->p_memsz)
			top = phdr->p_vaddr + phdr->p_memsz;
	}

	/* allocate one big anon block for everything */
	mflags = MAP_PRIVATE;
	if (params->flags & ELF_FDPIC_FLAG_EXECUTABLE)
		mflags |= MAP_EXECUTABLE;

	maddr = vm_mmap(NULL, load_addr, top - base,
			PROT_READ | PROT_WRITE | PROT_EXEC, mflags, 0);
	if (IS_ERR_VALUE(maddr))
		return (int) maddr;

	if (load_addr != 0)
		load_addr += PAGE_ALIGN(top - base);

	/* and then load the file segments into it */
	phdr = params->phdrs;
	for (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) {
		if (params->phdrs[loop].p_type != PT_LOAD)
			continue;

		seg->addr = maddr + (phdr->p_vaddr - base);
		seg->p_vaddr = phdr->p_vaddr;
		seg->p_memsz = phdr->p_memsz;

		ret = read_code(file, seg->addr, phdr->p_offset,
				       phdr->p_filesz);
		if (ret < 0)
			return ret;

		/* map the ELF header address if in this segment */
		if (phdr->p_offset == 0)
			params->elfhdr_addr = seg->addr;

		/* clear any space allocated but not loaded */
		if (phdr->p_filesz < phdr->p_memsz) {
			if (clear_user((void *) (seg->addr + phdr->p_filesz),
				       phdr->p_memsz - phdr->p_filesz))
				return -EFAULT;
		}

		if (mm) {
			if (phdr->p_flags & PF_X) {
				if (!mm->start_code) {
					mm->start_code = seg->addr;
					mm->end_code = seg->addr +
						phdr->p_memsz;
				}
			} else if (!mm->start_data) {
				mm->start_data = seg->addr;
				mm->end_data = seg->addr + phdr->p_memsz;
			}
		}

		seg++;
	}

	return 0;
}