#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct vm_area_struct {int vm_flags; struct file* vm_file; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct inode {unsigned long i_size; int /*<<< orphan*/  i_ctime; struct address_space* i_mapping; } ;
struct hugetlbfs_inode_info {int seals; } ;
struct hstate {int dummy; } ;
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  unsigned long pgoff_t ;
typedef  unsigned long loff_t ;
struct TYPE_3__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EINTR ; 
 long EOPNOTSUPP ; 
 int EPERM ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int F_SEAL_GROW ; 
 struct hugetlbfs_inode_info* HUGETLBFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PTR_ERR (struct page*) ; 
 int VM_HUGETLB ; 
 int VM_MAYSHARE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  __SetPageUptodate (struct page*) ; 
 struct page* alloc_huge_page (struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  clear_huge_page (struct page*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 struct page* find_get_page (struct address_space*,unsigned long) ; 
 struct hstate* hstate_inode (struct inode*) ; 
 int huge_add_to_page_cache (struct page*,struct address_space*,unsigned long) ; 
 unsigned long huge_page_shift (struct hstate*) ; 
 unsigned long huge_page_size (struct hstate*) ; 
 int /*<<< orphan*/  hugetlb_drop_vma_policy (struct vm_area_struct*) ; 
 size_t hugetlb_fault_mutex_hash (struct hstate*,struct address_space*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * hugetlb_fault_mutex_table ; 
 int /*<<< orphan*/  hugetlb_set_vma_policy (struct vm_area_struct*,struct inode*,unsigned long) ; 
 long hugetlbfs_punch_hole (struct inode*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned long) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int inode_newsize_ok (struct inode*,unsigned long) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pages_per_huge_page (struct hstate*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ signal_pending (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  vma_init (struct vm_area_struct*,struct mm_struct*) ; 

__attribute__((used)) static long hugetlbfs_fallocate(struct file *file, int mode, loff_t offset,
				loff_t len)
{
	struct inode *inode = file_inode(file);
	struct hugetlbfs_inode_info *info = HUGETLBFS_I(inode);
	struct address_space *mapping = inode->i_mapping;
	struct hstate *h = hstate_inode(inode);
	struct vm_area_struct pseudo_vma;
	struct mm_struct *mm = current->mm;
	loff_t hpage_size = huge_page_size(h);
	unsigned long hpage_shift = huge_page_shift(h);
	pgoff_t start, index, end;
	int error;
	u32 hash;

	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		return -EOPNOTSUPP;

	if (mode & FALLOC_FL_PUNCH_HOLE)
		return hugetlbfs_punch_hole(inode, offset, len);

	/*
	 * Default preallocate case.
	 * For this range, start is rounded down and end is rounded up
	 * as well as being converted to page offsets.
	 */
	start = offset >> hpage_shift;
	end = (offset + len + hpage_size - 1) >> hpage_shift;

	inode_lock(inode);

	/* We need to check rlimit even when FALLOC_FL_KEEP_SIZE */
	error = inode_newsize_ok(inode, offset + len);
	if (error)
		goto out;

	if ((info->seals & F_SEAL_GROW) && offset + len > inode->i_size) {
		error = -EPERM;
		goto out;
	}

	/*
	 * Initialize a pseudo vma as this is required by the huge page
	 * allocation routines.  If NUMA is configured, use page index
	 * as input to create an allocation policy.
	 */
	vma_init(&pseudo_vma, mm);
	pseudo_vma.vm_flags = (VM_HUGETLB | VM_MAYSHARE | VM_SHARED);
	pseudo_vma.vm_file = file;

	for (index = start; index < end; index++) {
		/*
		 * This is supposed to be the vaddr where the page is being
		 * faulted in, but we have no vaddr here.
		 */
		struct page *page;
		unsigned long addr;
		int avoid_reserve = 0;

		cond_resched();

		/*
		 * fallocate(2) manpage permits EINTR; we may have been
		 * interrupted because we are using up too much memory.
		 */
		if (signal_pending(current)) {
			error = -EINTR;
			break;
		}

		/* Set numa allocation policy based on index */
		hugetlb_set_vma_policy(&pseudo_vma, inode, index);

		/* addr is the offset within the file (zero based) */
		addr = index * hpage_size;

		/* mutex taken here, fault path and hole punch */
		hash = hugetlb_fault_mutex_hash(h, mapping, index, addr);
		mutex_lock(&hugetlb_fault_mutex_table[hash]);

		/* See if already present in mapping to avoid alloc/free */
		page = find_get_page(mapping, index);
		if (page) {
			put_page(page);
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			hugetlb_drop_vma_policy(&pseudo_vma);
			continue;
		}

		/* Allocate page and add to page cache */
		page = alloc_huge_page(&pseudo_vma, addr, avoid_reserve);
		hugetlb_drop_vma_policy(&pseudo_vma);
		if (IS_ERR(page)) {
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			error = PTR_ERR(page);
			goto out;
		}
		clear_huge_page(page, addr, pages_per_huge_page(h));
		__SetPageUptodate(page);
		error = huge_add_to_page_cache(page, mapping, index);
		if (unlikely(error)) {
			put_page(page);
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			goto out;
		}

		mutex_unlock(&hugetlb_fault_mutex_table[hash]);

		/*
		 * unlock_page because locked by add_to_page_cache()
		 * page_put due to reference from alloc_huge_page()
		 */
		unlock_page(page);
		put_page(page);
	}

	if (!(mode & FALLOC_FL_KEEP_SIZE) && offset + len > inode->i_size)
		i_size_write(inode, offset + len);
	inode->i_ctime = current_time(inode);
out:
	inode_unlock(inode);
	return error;
}