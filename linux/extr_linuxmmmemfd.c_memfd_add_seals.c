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
struct inode {int dummy; } ;
struct file {int f_mode; int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int FMODE_WRITE ; 
 scalar_t__ F_ALL_SEALS ; 
 unsigned int F_SEAL_SEAL ; 
 unsigned int F_SEAL_WRITE ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mapping_allow_writable (int /*<<< orphan*/ ) ; 
 int mapping_deny_writable (int /*<<< orphan*/ ) ; 
 unsigned int* memfd_file_seals_ptr (struct file*) ; 
 int memfd_wait_for_pins (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memfd_add_seals(struct file *file, unsigned int seals)
{
	struct inode *inode = file_inode(file);
	unsigned int *file_seals;
	int error;

	/*
	 * SEALING
	 * Sealing allows multiple parties to share a tmpfs or hugetlbfs file
	 * but restrict access to a specific subset of file operations. Seals
	 * can only be added, but never removed. This way, mutually untrusted
	 * parties can share common memory regions with a well-defined policy.
	 * A malicious peer can thus never perform unwanted operations on a
	 * shared object.
	 *
	 * Seals are only supported on special tmpfs or hugetlbfs files and
	 * always affect the whole underlying inode. Once a seal is set, it
	 * may prevent some kinds of access to the file. Currently, the
	 * following seals are defined:
	 *   SEAL_SEAL: Prevent further seals from being set on this file
	 *   SEAL_SHRINK: Prevent the file from shrinking
	 *   SEAL_GROW: Prevent the file from growing
	 *   SEAL_WRITE: Prevent write access to the file
	 *
	 * As we don't require any trust relationship between two parties, we
	 * must prevent seals from being removed. Therefore, sealing a file
	 * only adds a given set of seals to the file, it never touches
	 * existing seals. Furthermore, the "setting seals"-operation can be
	 * sealed itself, which basically prevents any further seal from being
	 * added.
	 *
	 * Semantics of sealing are only defined on volatile files. Only
	 * anonymous tmpfs and hugetlbfs files support sealing. More
	 * importantly, seals are never written to disk. Therefore, there's
	 * no plan to support it on other file types.
	 */

	if (!(file->f_mode & FMODE_WRITE))
		return -EPERM;
	if (seals & ~(unsigned int)F_ALL_SEALS)
		return -EINVAL;

	inode_lock(inode);

	file_seals = memfd_file_seals_ptr(file);
	if (!file_seals) {
		error = -EINVAL;
		goto unlock;
	}

	if (*file_seals & F_SEAL_SEAL) {
		error = -EPERM;
		goto unlock;
	}

	if ((seals & F_SEAL_WRITE) && !(*file_seals & F_SEAL_WRITE)) {
		error = mapping_deny_writable(file->f_mapping);
		if (error)
			goto unlock;

		error = memfd_wait_for_pins(file->f_mapping);
		if (error) {
			mapping_allow_writable(file->f_mapping);
			goto unlock;
		}
	}

	*file_seals |= seals;
	error = 0;

unlock:
	inode_unlock(inode);
	return error;
}