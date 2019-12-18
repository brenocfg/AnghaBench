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
struct page {scalar_t__ index; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EACCES ; 
 int EBADF ; 
 int /*<<< orphan*/  FYI ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,struct page*,int,int) ; 
 int cifs_readpage_worker (struct file*,struct page*,int*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 

__attribute__((used)) static int cifs_readpage(struct file *file, struct page *page)
{
	loff_t offset = (loff_t)page->index << PAGE_SHIFT;
	int rc = -EACCES;
	unsigned int xid;

	xid = get_xid();

	if (file->private_data == NULL) {
		rc = -EBADF;
		free_xid(xid);
		return rc;
	}

	cifs_dbg(FYI, "readpage %p at offset %d 0x%x\n",
		 page, (int)offset, (int)offset);

	rc = cifs_readpage_worker(file, page, &offset);

	free_xid(xid);
	return rc;
}