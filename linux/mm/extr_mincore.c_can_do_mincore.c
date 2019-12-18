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

/* Variables and functions */
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ inode_owner_or_capable (int /*<<< orphan*/ ) ; 
 scalar_t__ inode_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vma_is_anonymous (struct vm_area_struct*) ; 

__attribute__((used)) static inline bool can_do_mincore(struct vm_area_struct *vma)
{
	if (vma_is_anonymous(vma))
		return true;
	if (!vma->vm_file)
		return false;
	/*
	 * Reveal pagecache information only for non-anonymous mappings that
	 * correspond to the files the calling process could (if tried) open
	 * for writing; otherwise we'd be including shared non-exclusive
	 * mappings, which opens a side channel.
	 */
	return inode_owner_or_capable(file_inode(vma->vm_file)) ||
		inode_permission(file_inode(vma->vm_file), MAY_WRITE) == 0;
}