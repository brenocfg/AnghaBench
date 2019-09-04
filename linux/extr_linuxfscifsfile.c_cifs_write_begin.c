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
struct page {int dummy; } ;
struct file {int f_flags; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 scalar_t__ CIFS_CACHE_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIFS_I (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FYI ; 
 int O_ACCMODE ; 
 int O_WRONLY ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageChecked (struct page*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,long long,unsigned int) ; 
 int /*<<< orphan*/  cifs_readpage_worker (struct file*,struct page*,int*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segments (struct page*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int cifs_write_begin(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata)
{
	int oncethru = 0;
	pgoff_t index = pos >> PAGE_SHIFT;
	loff_t offset = pos & (PAGE_SIZE - 1);
	loff_t page_start = pos & PAGE_MASK;
	loff_t i_size;
	struct page *page;
	int rc = 0;

	cifs_dbg(FYI, "write_begin from %lld len %d\n", (long long)pos, len);

start:
	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page) {
		rc = -ENOMEM;
		goto out;
	}

	if (PageUptodate(page))
		goto out;

	/*
	 * If we write a full page it will be up to date, no need to read from
	 * the server. If the write is short, we'll end up doing a sync write
	 * instead.
	 */
	if (len == PAGE_SIZE)
		goto out;

	/*
	 * optimize away the read when we have an oplock, and we're not
	 * expecting to use any of the data we'd be reading in. That
	 * is, when the page lies beyond the EOF, or straddles the EOF
	 * and the write will cover all of the existing data.
	 */
	if (CIFS_CACHE_READ(CIFS_I(mapping->host))) {
		i_size = i_size_read(mapping->host);
		if (page_start >= i_size ||
		    (offset == 0 && (pos + len) >= i_size)) {
			zero_user_segments(page, 0, offset,
					   offset + len,
					   PAGE_SIZE);
			/*
			 * PageChecked means that the parts of the page
			 * to which we're not writing are considered up
			 * to date. Once the data is copied to the
			 * page, it can be set uptodate.
			 */
			SetPageChecked(page);
			goto out;
		}
	}

	if ((file->f_flags & O_ACCMODE) != O_WRONLY && !oncethru) {
		/*
		 * might as well read a page, it is fast enough. If we get
		 * an error, we don't need to return it. cifs_write_end will
		 * do a sync write instead since PG_uptodate isn't set.
		 */
		cifs_readpage_worker(file, page, &page_start);
		put_page(page);
		oncethru = 1;
		goto start;
	} else {
		/* we could try using another file handle if there is one -
		   but how would we lock it to prevent close of that handle
		   racing with this read? In any case
		   this will be written out by write_end so is fine */
	}
out:
	*pagep = page;
	return rc;
}