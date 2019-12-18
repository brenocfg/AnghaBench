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
struct shmid_kernel {int /*<<< orphan*/  shm_file; } ;
struct shmem_inode_info {int /*<<< orphan*/  lock; scalar_t__ swapped; } ;
struct inode {struct address_space* i_mapping; } ;
struct hstate {int dummy; } ;
struct address_space {unsigned long nrpages; } ;

/* Variables and functions */
 struct shmem_inode_info* SHMEM_I (struct inode*) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 struct hstate* hstate_file (int /*<<< orphan*/ ) ; 
 scalar_t__ is_file_hugepages (int /*<<< orphan*/ ) ; 
 unsigned long pages_per_huge_page (struct hstate*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void shm_add_rss_swap(struct shmid_kernel *shp,
	unsigned long *rss_add, unsigned long *swp_add)
{
	struct inode *inode;

	inode = file_inode(shp->shm_file);

	if (is_file_hugepages(shp->shm_file)) {
		struct address_space *mapping = inode->i_mapping;
		struct hstate *h = hstate_file(shp->shm_file);
		*rss_add += pages_per_huge_page(h) * mapping->nrpages;
	} else {
#ifdef CONFIG_SHMEM
		struct shmem_inode_info *info = SHMEM_I(inode);

		spin_lock_irq(&info->lock);
		*rss_add += inode->i_mapping->nrpages;
		*swp_add += info->swapped;
		spin_unlock_irq(&info->lock);
#else
		*rss_add += inode->i_mapping->nrpages;
#endif
	}
}