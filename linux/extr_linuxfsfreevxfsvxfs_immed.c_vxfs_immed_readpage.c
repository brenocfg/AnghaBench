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
typedef  int u_int64_t ;
struct TYPE_4__ {int vi_immed; } ;
struct vxfs_inode_info {TYPE_2__ vii_immed; } ;
struct page {scalar_t__ index; TYPE_1__* mapping; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 struct vxfs_inode_info* VXFS_INO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int
vxfs_immed_readpage(struct file *fp, struct page *pp)
{
	struct vxfs_inode_info	*vip = VXFS_INO(pp->mapping->host);
	u_int64_t	offset = (u_int64_t)pp->index << PAGE_SHIFT;
	caddr_t		kaddr;

	kaddr = kmap(pp);
	memcpy(kaddr, vip->vii_immed.vi_immed + offset, PAGE_SIZE);
	kunmap(pp);
	
	flush_dcache_page(pp);
	SetPageUptodate(pp);
        unlock_page(pp);

	return 0;
}