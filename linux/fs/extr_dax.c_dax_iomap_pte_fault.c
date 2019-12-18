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
typedef  int vm_fault_t ;
struct vm_fault {unsigned long address; int flags; scalar_t__ cow_page; int /*<<< orphan*/ * pmd; scalar_t__ pgoff; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; TYPE_1__* vm_file; } ;
struct iomap_ops {int (* iomap_begin ) (struct inode*,scalar_t__,int,unsigned int,struct iomap*) ;int /*<<< orphan*/  (* iomap_end ) (struct inode*,scalar_t__,int,int,unsigned int,struct iomap*) ;} ;
struct iomap {scalar_t__ offset; scalar_t__ length; int type; int flags; int /*<<< orphan*/  dax_dev; int /*<<< orphan*/  bdev; int /*<<< orphan*/  member_0; } ;
struct inode {int dummy; } ;
struct address_space {struct inode* host; int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  pfn_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 int EIO ; 
 int FAULT_FLAG_WRITE ; 
 unsigned int IOMAP_FAULT ; 
 int IOMAP_F_NEW ; 
#define  IOMAP_HOLE 130 
#define  IOMAP_MAPPED 129 
#define  IOMAP_UNWRITTEN 128 
 unsigned int IOMAP_WRITE ; 
 scalar_t__ PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PGMAJFAULT ; 
 int VM_FAULT_DONE_COW ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_NEEDDSYNC ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_SIGBUS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  __SetPageUptodate (scalar_t__) ; 
 int /*<<< orphan*/  clear_user_highpage (scalar_t__,unsigned long) ; 
 int copy_user_dax (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  count_memcg_event_mm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int dax_fault_is_synchronous (unsigned int,struct vm_area_struct*,struct iomap*) ; 
 int dax_fault_return (int) ; 
 void* dax_insert_entry (int /*<<< orphan*/ *,struct address_space*,struct vm_fault*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dax_iomap_pfn (struct iomap*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_iomap_sector (struct iomap*,scalar_t__) ; 
 int dax_load_hole (int /*<<< orphan*/ *,struct address_space*,void**,struct vm_fault*) ; 
 int /*<<< orphan*/  dax_unlock_entry (int /*<<< orphan*/ *,void*) ; 
 int finish_fault (struct vm_fault*) ; 
 void* grab_mapping_entry (int /*<<< orphan*/ *,struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,scalar_t__,int,unsigned int,struct iomap*) ; 
 int /*<<< orphan*/  stub2 (struct inode*,scalar_t__,int,int,unsigned int,struct iomap*) ; 
 int /*<<< orphan*/  trace_dax_insert_mapping (struct inode*,struct vm_fault*,void*) ; 
 int /*<<< orphan*/  trace_dax_pte_fault (struct inode*,struct vm_fault*,int) ; 
 int /*<<< orphan*/  trace_dax_pte_fault_done (struct inode*,struct vm_fault*,int) ; 
 int vmf_insert_mixed (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int vmf_insert_mixed_mkwrite (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ xa_is_internal (void*) ; 
 int xa_to_internal (void*) ; 
 int /*<<< orphan*/  xas ; 

__attribute__((used)) static vm_fault_t dax_iomap_pte_fault(struct vm_fault *vmf, pfn_t *pfnp,
			       int *iomap_errp, const struct iomap_ops *ops)
{
	struct vm_area_struct *vma = vmf->vma;
	struct address_space *mapping = vma->vm_file->f_mapping;
	XA_STATE(xas, &mapping->i_pages, vmf->pgoff);
	struct inode *inode = mapping->host;
	unsigned long vaddr = vmf->address;
	loff_t pos = (loff_t)vmf->pgoff << PAGE_SHIFT;
	struct iomap iomap = { 0 };
	unsigned flags = IOMAP_FAULT;
	int error, major = 0;
	bool write = vmf->flags & FAULT_FLAG_WRITE;
	bool sync;
	vm_fault_t ret = 0;
	void *entry;
	pfn_t pfn;

	trace_dax_pte_fault(inode, vmf, ret);
	/*
	 * Check whether offset isn't beyond end of file now. Caller is supposed
	 * to hold locks serializing us with truncate / punch hole so this is
	 * a reliable test.
	 */
	if (pos >= i_size_read(inode)) {
		ret = VM_FAULT_SIGBUS;
		goto out;
	}

	if (write && !vmf->cow_page)
		flags |= IOMAP_WRITE;

	entry = grab_mapping_entry(&xas, mapping, 0);
	if (xa_is_internal(entry)) {
		ret = xa_to_internal(entry);
		goto out;
	}

	/*
	 * It is possible, particularly with mixed reads & writes to private
	 * mappings, that we have raced with a PMD fault that overlaps with
	 * the PTE we need to set up.  If so just return and the fault will be
	 * retried.
	 */
	if (pmd_trans_huge(*vmf->pmd) || pmd_devmap(*vmf->pmd)) {
		ret = VM_FAULT_NOPAGE;
		goto unlock_entry;
	}

	/*
	 * Note that we don't bother to use iomap_apply here: DAX required
	 * the file system block size to be equal the page size, which means
	 * that we never have to deal with more than a single extent here.
	 */
	error = ops->iomap_begin(inode, pos, PAGE_SIZE, flags, &iomap);
	if (iomap_errp)
		*iomap_errp = error;
	if (error) {
		ret = dax_fault_return(error);
		goto unlock_entry;
	}
	if (WARN_ON_ONCE(iomap.offset + iomap.length < pos + PAGE_SIZE)) {
		error = -EIO;	/* fs corruption? */
		goto error_finish_iomap;
	}

	if (vmf->cow_page) {
		sector_t sector = dax_iomap_sector(&iomap, pos);

		switch (iomap.type) {
		case IOMAP_HOLE:
		case IOMAP_UNWRITTEN:
			clear_user_highpage(vmf->cow_page, vaddr);
			break;
		case IOMAP_MAPPED:
			error = copy_user_dax(iomap.bdev, iomap.dax_dev,
					sector, PAGE_SIZE, vmf->cow_page, vaddr);
			break;
		default:
			WARN_ON_ONCE(1);
			error = -EIO;
			break;
		}

		if (error)
			goto error_finish_iomap;

		__SetPageUptodate(vmf->cow_page);
		ret = finish_fault(vmf);
		if (!ret)
			ret = VM_FAULT_DONE_COW;
		goto finish_iomap;
	}

	sync = dax_fault_is_synchronous(flags, vma, &iomap);

	switch (iomap.type) {
	case IOMAP_MAPPED:
		if (iomap.flags & IOMAP_F_NEW) {
			count_vm_event(PGMAJFAULT);
			count_memcg_event_mm(vma->vm_mm, PGMAJFAULT);
			major = VM_FAULT_MAJOR;
		}
		error = dax_iomap_pfn(&iomap, pos, PAGE_SIZE, &pfn);
		if (error < 0)
			goto error_finish_iomap;

		entry = dax_insert_entry(&xas, mapping, vmf, entry, pfn,
						 0, write && !sync);

		/*
		 * If we are doing synchronous page fault and inode needs fsync,
		 * we can insert PTE into page tables only after that happens.
		 * Skip insertion for now and return the pfn so that caller can
		 * insert it after fsync is done.
		 */
		if (sync) {
			if (WARN_ON_ONCE(!pfnp)) {
				error = -EIO;
				goto error_finish_iomap;
			}
			*pfnp = pfn;
			ret = VM_FAULT_NEEDDSYNC | major;
			goto finish_iomap;
		}
		trace_dax_insert_mapping(inode, vmf, entry);
		if (write)
			ret = vmf_insert_mixed_mkwrite(vma, vaddr, pfn);
		else
			ret = vmf_insert_mixed(vma, vaddr, pfn);

		goto finish_iomap;
	case IOMAP_UNWRITTEN:
	case IOMAP_HOLE:
		if (!write) {
			ret = dax_load_hole(&xas, mapping, &entry, vmf);
			goto finish_iomap;
		}
		/*FALLTHRU*/
	default:
		WARN_ON_ONCE(1);
		error = -EIO;
		break;
	}

 error_finish_iomap:
	ret = dax_fault_return(error);
 finish_iomap:
	if (ops->iomap_end) {
		int copied = PAGE_SIZE;

		if (ret & VM_FAULT_ERROR)
			copied = 0;
		/*
		 * The fault is done by now and there's no way back (other
		 * thread may be already happily using PTE we have installed).
		 * Just ignore error from ->iomap_end since we cannot do much
		 * with it.
		 */
		ops->iomap_end(inode, pos, PAGE_SIZE, copied, flags, &iomap);
	}
 unlock_entry:
	dax_unlock_entry(&xas, entry);
 out:
	trace_dax_pte_fault_done(inode, vmf, ret);
	return ret | major;
}