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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct cifs_writedata {unsigned int bytes; int nr_pages; unsigned int pagesz; unsigned int tailsz; int /*<<< orphan*/  refcount; int /*<<< orphan*/ * pages; TYPE_4__* cfile; int /*<<< orphan*/  pid; int /*<<< orphan*/  offset; int /*<<< orphan*/  sync_mode; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  tlink; int /*<<< orphan*/  dentry; } ;
struct TYPE_7__ {TYPE_1__* ses; } ;
struct TYPE_6__ {unsigned int (* wp_retry_size ) (struct inode*) ;int (* async_writev ) (struct cifs_writedata*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_I (struct inode*) ; 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EBADF ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int cifs_get_writable_file (int /*<<< orphan*/ ,int,TYPE_4__**) ; 
 struct cifs_writedata* cifs_writedata_alloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_writedata_release ; 
 int /*<<< orphan*/  cifs_writev_complete ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (int /*<<< orphan*/ ) ; 
 scalar_t__ is_retryable_error (int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct inode*) ; 
 int stub2 (struct cifs_writedata*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tlink_tcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cifs_writev_requeue(struct cifs_writedata *wdata)
{
	int i, rc = 0;
	struct inode *inode = d_inode(wdata->cfile->dentry);
	struct TCP_Server_Info *server;
	unsigned int rest_len;

	server = tlink_tcon(wdata->cfile->tlink)->ses->server;
	i = 0;
	rest_len = wdata->bytes;
	do {
		struct cifs_writedata *wdata2;
		unsigned int j, nr_pages, wsize, tailsz, cur_len;

		wsize = server->ops->wp_retry_size(inode);
		if (wsize < rest_len) {
			nr_pages = wsize / PAGE_SIZE;
			if (!nr_pages) {
				rc = -ENOTSUPP;
				break;
			}
			cur_len = nr_pages * PAGE_SIZE;
			tailsz = PAGE_SIZE;
		} else {
			nr_pages = DIV_ROUND_UP(rest_len, PAGE_SIZE);
			cur_len = rest_len;
			tailsz = rest_len - (nr_pages - 1) * PAGE_SIZE;
		}

		wdata2 = cifs_writedata_alloc(nr_pages, cifs_writev_complete);
		if (!wdata2) {
			rc = -ENOMEM;
			break;
		}

		for (j = 0; j < nr_pages; j++) {
			wdata2->pages[j] = wdata->pages[i + j];
			lock_page(wdata2->pages[j]);
			clear_page_dirty_for_io(wdata2->pages[j]);
		}

		wdata2->sync_mode = wdata->sync_mode;
		wdata2->nr_pages = nr_pages;
		wdata2->offset = page_offset(wdata2->pages[0]);
		wdata2->pagesz = PAGE_SIZE;
		wdata2->tailsz = tailsz;
		wdata2->bytes = cur_len;

		rc = cifs_get_writable_file(CIFS_I(inode), false,
					    &wdata2->cfile);
		if (!wdata2->cfile) {
			cifs_dbg(VFS, "No writable handle to retry writepages rc=%d\n",
				 rc);
			if (!is_retryable_error(rc))
				rc = -EBADF;
		} else {
			wdata2->pid = wdata2->cfile->pid;
			rc = server->ops->async_writev(wdata2,
						       cifs_writedata_release);
		}

		for (j = 0; j < nr_pages; j++) {
			unlock_page(wdata2->pages[j]);
			if (rc != 0 && !is_retryable_error(rc)) {
				SetPageError(wdata2->pages[j]);
				end_page_writeback(wdata2->pages[j]);
				put_page(wdata2->pages[j]);
			}
		}

		if (rc) {
			kref_put(&wdata2->refcount, cifs_writedata_release);
			if (is_retryable_error(rc))
				continue;
			i += nr_pages;
			break;
		}

		rest_len -= cur_len;
		i += nr_pages;
	} while (i < wdata->nr_pages);

	/* cleanup remaining pages from the original wdata */
	for (; i < wdata->nr_pages; i++) {
		SetPageError(wdata->pages[i]);
		end_page_writeback(wdata->pages[i]);
		put_page(wdata->pages[i]);
	}

	if (rc != 0 && !is_retryable_error(rc))
		mapping_set_error(inode->i_mapping, rc);
	kref_put(&wdata->refcount, cifs_writedata_release);
}