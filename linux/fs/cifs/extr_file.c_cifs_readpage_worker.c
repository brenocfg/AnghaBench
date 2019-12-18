#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_5__ {void* i_atime; void* i_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int cifs_read (struct file*,char*,int,int /*<<< orphan*/ *) ; 
 int cifs_readpage_from_fscache (TYPE_1__*,struct page*) ; 
 int /*<<< orphan*/  cifs_readpage_to_fscache (TYPE_1__*,struct page*) ; 
 void* current_time (TYPE_1__*) ; 
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ timespec64_compare (void**,void**) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int cifs_readpage_worker(struct file *file, struct page *page,
	loff_t *poffset)
{
	char *read_data;
	int rc;

	/* Is the page cached? */
	rc = cifs_readpage_from_fscache(file_inode(file), page);
	if (rc == 0)
		goto read_complete;

	read_data = kmap(page);
	/* for reads over a certain size could initiate async read ahead */

	rc = cifs_read(file, read_data, PAGE_SIZE, poffset);

	if (rc < 0)
		goto io_error;
	else
		cifs_dbg(FYI, "Bytes read %d\n", rc);

	/* we do not want atime to be less than mtime, it broke some apps */
	file_inode(file)->i_atime = current_time(file_inode(file));
	if (timespec64_compare(&(file_inode(file)->i_atime), &(file_inode(file)->i_mtime)))
		file_inode(file)->i_atime = file_inode(file)->i_mtime;
	else
		file_inode(file)->i_atime = current_time(file_inode(file));

	if (PAGE_SIZE > rc)
		memset(read_data + rc, 0, PAGE_SIZE - rc);

	flush_dcache_page(page);
	SetPageUptodate(page);

	/* send this page to the cache */
	cifs_readpage_to_fscache(file_inode(file), page);

	rc = 0;

io_error:
	kunmap(page);
	unlock_page(page);

read_complete:
	return rc;
}