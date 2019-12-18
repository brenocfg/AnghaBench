#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;
struct nfs_pageio_descriptor {int pg_error; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_VFSWRITEPAGE ; 
 int /*<<< orphan*/  nfs_async_write_completion_ops ; 
 int nfs_do_writepage (struct page*,struct writeback_control*,struct nfs_pageio_descriptor*) ; 
 scalar_t__ nfs_error_is_fatal (int) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_complete (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_init_write (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 

__attribute__((used)) static int nfs_writepage_locked(struct page *page,
				struct writeback_control *wbc)
{
	struct nfs_pageio_descriptor pgio;
	struct inode *inode = page_file_mapping(page)->host;
	int err;

	nfs_inc_stats(inode, NFSIOS_VFSWRITEPAGE);
	nfs_pageio_init_write(&pgio, inode, 0,
				false, &nfs_async_write_completion_ops);
	err = nfs_do_writepage(page, wbc, &pgio);
	pgio.pg_error = 0;
	nfs_pageio_complete(&pgio);
	if (err < 0)
		return err;
	if (nfs_error_is_fatal(pgio.pg_error))
		return pgio.pg_error;
	return 0;
}