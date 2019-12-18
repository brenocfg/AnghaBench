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
struct vm_area_struct {int vm_flags; TYPE_1__* vm_file; } ;
struct resv_map {int dummy; } ;
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_2__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int HPAGE_RESV_MASK ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int VM_MAYSHARE ; 
 int get_vma_private_data (struct vm_area_struct*) ; 
 struct resv_map* inode_resv_map (struct inode*) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 

__attribute__((used)) static struct resv_map *vma_resv_map(struct vm_area_struct *vma)
{
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);
	if (vma->vm_flags & VM_MAYSHARE) {
		struct address_space *mapping = vma->vm_file->f_mapping;
		struct inode *inode = mapping->host;

		return inode_resv_map(inode);

	} else {
		return (struct resv_map *)(get_vma_private_data(vma) &
							~HPAGE_RESV_MASK);
	}
}