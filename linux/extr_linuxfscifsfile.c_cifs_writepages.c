#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int range_start; int range_end; scalar_t__ sync_mode; scalar_t__ nr_to_write; scalar_t__ range_cyclic; } ;
struct cifs_writedata {unsigned int credits; int /*<<< orphan*/  refcount; int /*<<< orphan*/ * pages; } ;
struct cifs_sb_info {unsigned int wsize; } ;
struct address_space {int writeback_index; TYPE_1__* host; } ;
struct TCP_Server_Info {TYPE_3__* ops; } ;
typedef  int pgoff_t ;
struct TYPE_8__ {TYPE_2__* ses; } ;
struct TYPE_7__ {int (* wait_mtu_credits ) (struct TCP_Server_Info*,unsigned int,unsigned int*,unsigned int*) ;} ;
struct TYPE_6__ {struct TCP_Server_Info* server; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int LLONG_MAX ; 
 int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  add_credits_and_wake_if (struct TCP_Server_Info*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_4__* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_writedata_release ; 
 int /*<<< orphan*/  end_page_writeback (int /*<<< orphan*/ ) ; 
 int generic_writepages (struct address_space*,struct writeback_control*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_error (struct address_space*,int) ; 
 int min (unsigned int,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,int /*<<< orphan*/ ) ; 
 int stub1 (struct TCP_Server_Info*,unsigned int,unsigned int*,unsigned int*) ; 
 struct cifs_writedata* wdata_alloc_and_fillpages (int,struct address_space*,int,int*,unsigned int*) ; 
 unsigned int wdata_prepare_pages (struct cifs_writedata*,unsigned int,struct address_space*,struct writeback_control*,int,int*,int*,int*) ; 
 int wdata_send_pages (struct cifs_writedata*,unsigned int,struct address_space*,struct writeback_control*) ; 

__attribute__((used)) static int cifs_writepages(struct address_space *mapping,
			   struct writeback_control *wbc)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(mapping->host->i_sb);
	struct TCP_Server_Info *server;
	bool done = false, scanned = false, range_whole = false;
	pgoff_t end, index;
	struct cifs_writedata *wdata;
	int rc = 0;

	/*
	 * If wsize is smaller than the page cache size, default to writing
	 * one page at a time via cifs_writepage
	 */
	if (cifs_sb->wsize < PAGE_SIZE)
		return generic_writepages(mapping, wbc);

	if (wbc->range_cyclic) {
		index = mapping->writeback_index; /* Start from prev offset */
		end = -1;
	} else {
		index = wbc->range_start >> PAGE_SHIFT;
		end = wbc->range_end >> PAGE_SHIFT;
		if (wbc->range_start == 0 && wbc->range_end == LLONG_MAX)
			range_whole = true;
		scanned = true;
	}
	server = cifs_sb_master_tcon(cifs_sb)->ses->server;
retry:
	while (!done && index <= end) {
		unsigned int i, nr_pages, found_pages, wsize, credits;
		pgoff_t next = 0, tofind, saved_index = index;

		rc = server->ops->wait_mtu_credits(server, cifs_sb->wsize,
						   &wsize, &credits);
		if (rc)
			break;

		tofind = min((wsize / PAGE_SIZE) - 1, end - index) + 1;

		wdata = wdata_alloc_and_fillpages(tofind, mapping, end, &index,
						  &found_pages);
		if (!wdata) {
			rc = -ENOMEM;
			add_credits_and_wake_if(server, credits, 0);
			break;
		}

		if (found_pages == 0) {
			kref_put(&wdata->refcount, cifs_writedata_release);
			add_credits_and_wake_if(server, credits, 0);
			break;
		}

		nr_pages = wdata_prepare_pages(wdata, found_pages, mapping, wbc,
					       end, &index, &next, &done);

		/* nothing to write? */
		if (nr_pages == 0) {
			kref_put(&wdata->refcount, cifs_writedata_release);
			add_credits_and_wake_if(server, credits, 0);
			continue;
		}

		wdata->credits = credits;

		rc = wdata_send_pages(wdata, nr_pages, mapping, wbc);

		/* send failure -- clean up the mess */
		if (rc != 0) {
			add_credits_and_wake_if(server, wdata->credits, 0);
			for (i = 0; i < nr_pages; ++i) {
				if (rc == -EAGAIN)
					redirty_page_for_writepage(wbc,
							   wdata->pages[i]);
				else
					SetPageError(wdata->pages[i]);
				end_page_writeback(wdata->pages[i]);
				put_page(wdata->pages[i]);
			}
			if (rc != -EAGAIN)
				mapping_set_error(mapping, rc);
		}
		kref_put(&wdata->refcount, cifs_writedata_release);

		if (wbc->sync_mode == WB_SYNC_ALL && rc == -EAGAIN) {
			index = saved_index;
			continue;
		}

		wbc->nr_to_write -= nr_pages;
		if (wbc->nr_to_write <= 0)
			done = true;

		index = next;
	}

	if (!scanned && !done) {
		/*
		 * We hit the last page and there is more work to be done: wrap
		 * back to the start of the file
		 */
		scanned = true;
		index = 0;
		goto retry;
	}

	if (wbc->range_cyclic || (range_whole && wbc->nr_to_write > 0))
		mapping->writeback_index = index;

	return rc;
}