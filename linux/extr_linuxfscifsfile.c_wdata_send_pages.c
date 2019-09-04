#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int /*<<< orphan*/  sync_mode; } ;
struct cifs_writedata {unsigned int nr_pages; unsigned int pagesz; int /*<<< orphan*/ * pages; TYPE_4__* cfile; int /*<<< orphan*/  pid; scalar_t__ tailsz; scalar_t__ bytes; scalar_t__ offset; int /*<<< orphan*/  sync_mode; } ;
struct address_space {int /*<<< orphan*/  host; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_9__ {int /*<<< orphan*/  tlink; int /*<<< orphan*/  pid; } ;
struct TYPE_8__ {TYPE_1__* ses; } ;
struct TYPE_7__ {int (* async_writev ) (struct cifs_writedata*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_I (int /*<<< orphan*/ ) ; 
 int EBADF ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifsFileInfo_put (TYPE_4__*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cifs_writedata_release ; 
 TYPE_4__* find_writable_file (int /*<<< orphan*/ ,int) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ page_offset (int /*<<< orphan*/ ) ; 
 int stub1 (struct cifs_writedata*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tlink_tcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wdata_send_pages(struct cifs_writedata *wdata, unsigned int nr_pages,
		 struct address_space *mapping, struct writeback_control *wbc)
{
	int rc = 0;
	struct TCP_Server_Info *server;
	unsigned int i;

	wdata->sync_mode = wbc->sync_mode;
	wdata->nr_pages = nr_pages;
	wdata->offset = page_offset(wdata->pages[0]);
	wdata->pagesz = PAGE_SIZE;
	wdata->tailsz = min(i_size_read(mapping->host) -
			page_offset(wdata->pages[nr_pages - 1]),
			(loff_t)PAGE_SIZE);
	wdata->bytes = ((nr_pages - 1) * PAGE_SIZE) + wdata->tailsz;

	if (wdata->cfile != NULL)
		cifsFileInfo_put(wdata->cfile);
	wdata->cfile = find_writable_file(CIFS_I(mapping->host), false);
	if (!wdata->cfile) {
		cifs_dbg(VFS, "No writable handles for inode\n");
		rc = -EBADF;
	} else {
		wdata->pid = wdata->cfile->pid;
		server = tlink_tcon(wdata->cfile->tlink)->ses->server;
		rc = server->ops->async_writev(wdata, cifs_writedata_release);
	}

	for (i = 0; i < nr_pages; ++i)
		unlock_page(wdata->pages[i]);

	return rc;
}