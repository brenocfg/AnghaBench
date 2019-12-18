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
struct vm_area_struct {TYPE_1__* vm_file; } ;
struct page {int dummy; } ;
struct TYPE_4__ {scalar_t__* e_ident; scalar_t__ e_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  f_mapping; } ;
typedef  TYPE_2__ Elf32_Ehdr ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS32 ; 
 scalar_t__ ELFCLASS64 ; 
 int /*<<< orphan*/  ELFMAG ; 
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 
 int /*<<< orphan*/  SELFMAG ; 
 struct page* find_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int stack_map_get_build_id_32 (void*,unsigned char*) ; 
 int stack_map_get_build_id_64 (void*,unsigned char*) ; 

__attribute__((used)) static int stack_map_get_build_id(struct vm_area_struct *vma,
				  unsigned char *build_id)
{
	Elf32_Ehdr *ehdr;
	struct page *page;
	void *page_addr;
	int ret;

	/* only works for page backed storage  */
	if (!vma->vm_file)
		return -EINVAL;

	page = find_get_page(vma->vm_file->f_mapping, 0);
	if (!page)
		return -EFAULT;	/* page not mapped */

	ret = -EINVAL;
	page_addr = kmap_atomic(page);
	ehdr = (Elf32_Ehdr *)page_addr;

	/* compare magic x7f "ELF" */
	if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
		goto out;

	/* only support executable file and shared object file */
	if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN)
		goto out;

	if (ehdr->e_ident[EI_CLASS] == ELFCLASS32)
		ret = stack_map_get_build_id_32(page_addr, build_id);
	else if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
		ret = stack_map_get_build_id_64(page_addr, build_id);
out:
	kunmap_atomic(page_addr);
	put_page(page);
	return ret;
}