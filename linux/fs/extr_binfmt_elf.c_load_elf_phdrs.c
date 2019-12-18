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
struct file {int dummy; } ;
struct elfhdr {int e_phentsize; int e_phnum; int /*<<< orphan*/  e_phoff; } ;
struct elf_phdr {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 unsigned int ELF_MIN_ALIGN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int kernel_read (struct file*,struct elf_phdr*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct elf_phdr*) ; 
 struct elf_phdr* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct elf_phdr *load_elf_phdrs(const struct elfhdr *elf_ex,
				       struct file *elf_file)
{
	struct elf_phdr *elf_phdata = NULL;
	int retval, err = -1;
	loff_t pos = elf_ex->e_phoff;
	unsigned int size;

	/*
	 * If the size of this structure has changed, then punt, since
	 * we will be doing the wrong thing.
	 */
	if (elf_ex->e_phentsize != sizeof(struct elf_phdr))
		goto out;

	/* Sanity check the number of program headers... */
	/* ...and their total size. */
	size = sizeof(struct elf_phdr) * elf_ex->e_phnum;
	if (size == 0 || size > 65536 || size > ELF_MIN_ALIGN)
		goto out;

	elf_phdata = kmalloc(size, GFP_KERNEL);
	if (!elf_phdata)
		goto out;

	/* Read in the program headers */
	retval = kernel_read(elf_file, elf_phdata, size, &pos);
	if (retval != size) {
		err = (retval < 0) ? retval : -EIO;
		goto out;
	}

	/* Success! */
	err = 0;
out:
	if (err) {
		kfree(elf_phdata);
		elf_phdata = NULL;
	}
	return elf_phdata;
}