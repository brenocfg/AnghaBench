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
struct vm_area_struct {int /*<<< orphan*/  vm_file; } ;
struct hugepage_subpool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 
 struct hugepage_subpool* subpool_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hugepage_subpool *subpool_vma(struct vm_area_struct *vma)
{
	return subpool_inode(file_inode(vma->vm_file));
}