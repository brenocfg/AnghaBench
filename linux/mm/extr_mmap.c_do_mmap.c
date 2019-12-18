#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_flags_t ;
struct vm_area_struct {unsigned long vm_start; } ;
struct mm_struct {scalar_t__ map_count; int def_flags; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct file {int f_mode; TYPE_2__* f_op; int /*<<< orphan*/  f_path; TYPE_1__* f_mapping; } ;
struct TYPE_6__ {int personality; struct mm_struct* mm; } ;
struct TYPE_5__ {unsigned long mmap_supported_flags; int /*<<< orphan*/  mmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 unsigned long EACCES ; 
 unsigned long EAGAIN ; 
 unsigned long EEXIST ; 
 unsigned long EINVAL ; 
 unsigned long ENODEV ; 
 unsigned long ENOMEM ; 
 unsigned long EOPNOTSUPP ; 
 unsigned long EOVERFLOW ; 
 unsigned long EPERM ; 
 unsigned long ETXTBSY ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  IS_APPEND (struct inode*) ; 
 int /*<<< orphan*/  IS_ERR_VALUE (unsigned long) ; 
 int /*<<< orphan*/  IS_SWAPFILE (int /*<<< orphan*/ ) ; 
 unsigned long LEGACY_MAP_MASK ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_FIXED_NOREPLACE ; 
 unsigned long MAP_LOCKED ; 
 unsigned long MAP_NONBLOCK ; 
 unsigned long MAP_NORESERVE ; 
 unsigned long MAP_POPULATE ; 
#define  MAP_PRIVATE 130 
#define  MAP_SHARED 129 
#define  MAP_SHARED_VALIDATE 128 
 unsigned long MAP_TYPE ; 
 scalar_t__ OVERCOMMIT_NEVER ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PROT_EXEC ; 
 unsigned long PROT_READ ; 
 unsigned long PROT_WRITE ; 
 int READ_IMPLIES_EXEC ; 
 int VM_EXEC ; 
 int VM_GROWSDOWN ; 
 int VM_GROWSUP ; 
 int VM_LOCKED ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_MAYSHARE ; 
 int VM_MAYWRITE ; 
 int VM_NORESERVE ; 
 int VM_SHARED ; 
 int calc_vm_flag_bits (unsigned long) ; 
 int calc_vm_prot_bits (unsigned long,int) ; 
 int /*<<< orphan*/  can_do_mlock () ; 
 TYPE_3__* current ; 
 int execute_only_pkey (struct mm_struct*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_mmap_ok (struct file*,struct inode*,unsigned long,unsigned long) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 unsigned long get_unmapped_area (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ is_file_hugepages (struct file*) ; 
 int /*<<< orphan*/  locks_verify_locked (struct file*) ; 
 scalar_t__ mlock_future_check (struct mm_struct*,int,unsigned long) ; 
 unsigned long mmap_region (struct file*,unsigned long,unsigned long,int,unsigned long,struct list_head*) ; 
 scalar_t__ offset_in_page (unsigned long) ; 
 scalar_t__ path_noexec (int /*<<< orphan*/ *) ; 
 unsigned long round_hint_to_min (unsigned long) ; 
 scalar_t__ sysctl_max_map_count ; 
 scalar_t__ sysctl_overcommit_memory ; 

unsigned long do_mmap(struct file *file, unsigned long addr,
			unsigned long len, unsigned long prot,
			unsigned long flags, vm_flags_t vm_flags,
			unsigned long pgoff, unsigned long *populate,
			struct list_head *uf)
{
	struct mm_struct *mm = current->mm;
	int pkey = 0;

	*populate = 0;

	if (!len)
		return -EINVAL;

	/*
	 * Does the application expect PROT_READ to imply PROT_EXEC?
	 *
	 * (the exception is when the underlying filesystem is noexec
	 *  mounted, in which case we dont add PROT_EXEC.)
	 */
	if ((prot & PROT_READ) && (current->personality & READ_IMPLIES_EXEC))
		if (!(file && path_noexec(&file->f_path)))
			prot |= PROT_EXEC;

	/* force arch specific MAP_FIXED handling in get_unmapped_area */
	if (flags & MAP_FIXED_NOREPLACE)
		flags |= MAP_FIXED;

	if (!(flags & MAP_FIXED))
		addr = round_hint_to_min(addr);

	/* Careful about overflows.. */
	len = PAGE_ALIGN(len);
	if (!len)
		return -ENOMEM;

	/* offset overflow? */
	if ((pgoff + (len >> PAGE_SHIFT)) < pgoff)
		return -EOVERFLOW;

	/* Too many mappings? */
	if (mm->map_count > sysctl_max_map_count)
		return -ENOMEM;

	/* Obtain the address to map to. we verify (or select) it and ensure
	 * that it represents a valid section of the address space.
	 */
	addr = get_unmapped_area(file, addr, len, pgoff, flags);
	if (offset_in_page(addr))
		return addr;

	if (flags & MAP_FIXED_NOREPLACE) {
		struct vm_area_struct *vma = find_vma(mm, addr);

		if (vma && vma->vm_start < addr + len)
			return -EEXIST;
	}

	if (prot == PROT_EXEC) {
		pkey = execute_only_pkey(mm);
		if (pkey < 0)
			pkey = 0;
	}

	/* Do simple checking here so the lower-level routines won't have
	 * to. we assume access permissions have been handled by the open
	 * of the memory object, so we don't do any here.
	 */
	vm_flags |= calc_vm_prot_bits(prot, pkey) | calc_vm_flag_bits(flags) |
			mm->def_flags | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC;

	if (flags & MAP_LOCKED)
		if (!can_do_mlock())
			return -EPERM;

	if (mlock_future_check(mm, vm_flags, len))
		return -EAGAIN;

	if (file) {
		struct inode *inode = file_inode(file);
		unsigned long flags_mask;

		if (!file_mmap_ok(file, inode, pgoff, len))
			return -EOVERFLOW;

		flags_mask = LEGACY_MAP_MASK | file->f_op->mmap_supported_flags;

		switch (flags & MAP_TYPE) {
		case MAP_SHARED:
			/*
			 * Force use of MAP_SHARED_VALIDATE with non-legacy
			 * flags. E.g. MAP_SYNC is dangerous to use with
			 * MAP_SHARED as you don't know which consistency model
			 * you will get. We silently ignore unsupported flags
			 * with MAP_SHARED to preserve backward compatibility.
			 */
			flags &= LEGACY_MAP_MASK;
			/* fall through */
		case MAP_SHARED_VALIDATE:
			if (flags & ~flags_mask)
				return -EOPNOTSUPP;
			if (prot & PROT_WRITE) {
				if (!(file->f_mode & FMODE_WRITE))
					return -EACCES;
				if (IS_SWAPFILE(file->f_mapping->host))
					return -ETXTBSY;
			}

			/*
			 * Make sure we don't allow writing to an append-only
			 * file..
			 */
			if (IS_APPEND(inode) && (file->f_mode & FMODE_WRITE))
				return -EACCES;

			/*
			 * Make sure there are no mandatory locks on the file.
			 */
			if (locks_verify_locked(file))
				return -EAGAIN;

			vm_flags |= VM_SHARED | VM_MAYSHARE;
			if (!(file->f_mode & FMODE_WRITE))
				vm_flags &= ~(VM_MAYWRITE | VM_SHARED);

			/* fall through */
		case MAP_PRIVATE:
			if (!(file->f_mode & FMODE_READ))
				return -EACCES;
			if (path_noexec(&file->f_path)) {
				if (vm_flags & VM_EXEC)
					return -EPERM;
				vm_flags &= ~VM_MAYEXEC;
			}

			if (!file->f_op->mmap)
				return -ENODEV;
			if (vm_flags & (VM_GROWSDOWN|VM_GROWSUP))
				return -EINVAL;
			break;

		default:
			return -EINVAL;
		}
	} else {
		switch (flags & MAP_TYPE) {
		case MAP_SHARED:
			if (vm_flags & (VM_GROWSDOWN|VM_GROWSUP))
				return -EINVAL;
			/*
			 * Ignore pgoff.
			 */
			pgoff = 0;
			vm_flags |= VM_SHARED | VM_MAYSHARE;
			break;
		case MAP_PRIVATE:
			/*
			 * Set pgoff according to addr for anon_vma.
			 */
			pgoff = addr >> PAGE_SHIFT;
			break;
		default:
			return -EINVAL;
		}
	}

	/*
	 * Set 'VM_NORESERVE' if we should not account for the
	 * memory use of this mapping.
	 */
	if (flags & MAP_NORESERVE) {
		/* We honor MAP_NORESERVE if allowed to overcommit */
		if (sysctl_overcommit_memory != OVERCOMMIT_NEVER)
			vm_flags |= VM_NORESERVE;

		/* hugetlb applies strict overcommit unless MAP_NORESERVE */
		if (file && is_file_hugepages(file))
			vm_flags |= VM_NORESERVE;
	}

	addr = mmap_region(file, addr, len, vm_flags, pgoff, uf);
	if (!IS_ERR_VALUE(addr) &&
	    ((vm_flags & VM_LOCKED) ||
	     (flags & (MAP_POPULATE | MAP_NONBLOCK)) == MAP_POPULATE))
		*populate = len;
	return addr;
}