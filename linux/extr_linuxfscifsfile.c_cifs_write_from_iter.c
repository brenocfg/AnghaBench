#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct iov_iter {int dummy; } ;
struct cifs_writedata {unsigned long nr_pages; size_t bytes; unsigned long pagesz; size_t tailsz; unsigned int credits; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; TYPE_5__* cfile; struct cifs_aio_ctx* ctx; int /*<<< orphan*/  pid; scalar_t__ offset; int /*<<< orphan*/  sync_mode; int /*<<< orphan*/ * pages; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  wsize; } ;
struct cifs_aio_ctx {int /*<<< orphan*/  refcount; } ;
struct cifsFileInfo {int /*<<< orphan*/  tlink; int /*<<< orphan*/  pid; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  scalar_t__ loff_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_11__ {int /*<<< orphan*/  invalidHandle; } ;
struct TYPE_10__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_9__ {TYPE_1__* ses; } ;
struct TYPE_8__ {int (* wait_mtu_credits ) (struct TCP_Server_Info*,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ;int (* async_writev ) (struct cifs_writedata*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int CIFS_MOUNT_RWPIDFORWARD ; 
 int EAGAIN ; 
 int ENOMEM ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int /*<<< orphan*/  add_credits_and_wake_if (struct TCP_Server_Info*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_5__* cifsFileInfo_get (struct cifsFileInfo*) ; 
 int cifs_reopen_file (TYPE_5__*,int) ; 
 int /*<<< orphan*/  cifs_uncached_writedata_release ; 
 int /*<<< orphan*/  cifs_uncached_writev_complete ; 
 int cifs_write_allocate_pages (int /*<<< orphan*/ *,unsigned long) ; 
 struct cifs_writedata* cifs_writedata_alloc (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 unsigned long get_numpages (unsigned int,size_t,size_t*) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cifs_writedata*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int stub1 (struct TCP_Server_Info*,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int stub2 (struct cifs_writedata*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tlink_tcon (int /*<<< orphan*/ ) ; 
 int wdata_fill_from_iovec (struct cifs_writedata*,struct iov_iter*,size_t*,unsigned long*) ; 

__attribute__((used)) static int
cifs_write_from_iter(loff_t offset, size_t len, struct iov_iter *from,
		     struct cifsFileInfo *open_file,
		     struct cifs_sb_info *cifs_sb, struct list_head *wdata_list,
		     struct cifs_aio_ctx *ctx)
{
	int rc = 0;
	size_t cur_len;
	unsigned long nr_pages, num_pages, i;
	struct cifs_writedata *wdata;
	struct iov_iter saved_from = *from;
	loff_t saved_offset = offset;
	pid_t pid;
	struct TCP_Server_Info *server;

	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_RWPIDFORWARD)
		pid = open_file->pid;
	else
		pid = current->tgid;

	server = tlink_tcon(open_file->tlink)->ses->server;

	do {
		unsigned int wsize, credits;

		rc = server->ops->wait_mtu_credits(server, cifs_sb->wsize,
						   &wsize, &credits);
		if (rc)
			break;

		nr_pages = get_numpages(wsize, len, &cur_len);
		wdata = cifs_writedata_alloc(nr_pages,
					     cifs_uncached_writev_complete);
		if (!wdata) {
			rc = -ENOMEM;
			add_credits_and_wake_if(server, credits, 0);
			break;
		}

		rc = cifs_write_allocate_pages(wdata->pages, nr_pages);
		if (rc) {
			kfree(wdata);
			add_credits_and_wake_if(server, credits, 0);
			break;
		}

		num_pages = nr_pages;
		rc = wdata_fill_from_iovec(wdata, from, &cur_len, &num_pages);
		if (rc) {
			for (i = 0; i < nr_pages; i++)
				put_page(wdata->pages[i]);
			kfree(wdata);
			add_credits_and_wake_if(server, credits, 0);
			break;
		}

		/*
		 * Bring nr_pages down to the number of pages we actually used,
		 * and free any pages that we didn't use.
		 */
		for ( ; nr_pages > num_pages; nr_pages--)
			put_page(wdata->pages[nr_pages - 1]);

		wdata->sync_mode = WB_SYNC_ALL;
		wdata->nr_pages = nr_pages;
		wdata->offset = (__u64)offset;
		wdata->cfile = cifsFileInfo_get(open_file);
		wdata->pid = pid;
		wdata->bytes = cur_len;
		wdata->pagesz = PAGE_SIZE;
		wdata->tailsz = cur_len - ((nr_pages - 1) * PAGE_SIZE);
		wdata->credits = credits;
		wdata->ctx = ctx;
		kref_get(&ctx->refcount);

		if (!wdata->cfile->invalidHandle ||
		    !(rc = cifs_reopen_file(wdata->cfile, false)))
			rc = server->ops->async_writev(wdata,
					cifs_uncached_writedata_release);
		if (rc) {
			add_credits_and_wake_if(server, wdata->credits, 0);
			kref_put(&wdata->refcount,
				 cifs_uncached_writedata_release);
			if (rc == -EAGAIN) {
				*from = saved_from;
				iov_iter_advance(from, offset - saved_offset);
				continue;
			}
			break;
		}

		list_add_tail(&wdata->list, wdata_list);
		offset += cur_len;
		len -= cur_len;
	} while (len > 0);

	return rc;
}