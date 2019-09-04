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
struct nfs_lock_context {int dummy; } ;
struct nfs_direct_req {size_t bytes_left; size_t max_count; int io_start; struct kiocb* iocb; struct nfs_lock_context* l_ctx; int /*<<< orphan*/  ctx; struct inode* inode; } ;
struct kiocb {int ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {scalar_t__ nrpages; struct inode* host; } ;
typedef  int ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FILE ; 
 scalar_t__ IS_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  NFSIOS_DIRECTWRITTENBYTES ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct file*,int,long long) ; 
 int generic_write_checks (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  generic_write_sync (struct kiocb*,int) ; 
 int /*<<< orphan*/  get_nfs_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_inode_pages2_range (struct address_space*,int,int) ; 
 int iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_revert (struct iov_iter*,int) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,size_t) ; 
 struct nfs_direct_req* nfs_direct_req_alloc () ; 
 int /*<<< orphan*/  nfs_direct_req_release (struct nfs_direct_req*) ; 
 int nfs_direct_wait (struct nfs_direct_req*) ; 
 int nfs_direct_write_schedule_iovec (struct nfs_direct_req*,struct iov_iter*,int) ; 
 int /*<<< orphan*/  nfs_end_io_direct (struct inode*) ; 
 int /*<<< orphan*/  nfs_file_open_context (struct file*) ; 
 struct nfs_lock_context* nfs_get_lock_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_start_io_direct (struct inode*) ; 
 int /*<<< orphan*/  task_io_account_write (size_t) ; 

ssize_t nfs_file_direct_write(struct kiocb *iocb, struct iov_iter *iter)
{
	ssize_t result = -EINVAL, requested;
	size_t count;
	struct file *file = iocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	struct inode *inode = mapping->host;
	struct nfs_direct_req *dreq;
	struct nfs_lock_context *l_ctx;
	loff_t pos, end;

	dfprintk(FILE, "NFS: direct write(%pD2, %zd@%Ld)\n",
		file, iov_iter_count(iter), (long long) iocb->ki_pos);

	result = generic_write_checks(iocb, iter);
	if (result <= 0)
		return result;
	count = result;
	nfs_add_stats(mapping->host, NFSIOS_DIRECTWRITTENBYTES, count);

	pos = iocb->ki_pos;
	end = (pos + iov_iter_count(iter) - 1) >> PAGE_SHIFT;

	task_io_account_write(count);

	result = -ENOMEM;
	dreq = nfs_direct_req_alloc();
	if (!dreq)
		goto out;

	dreq->inode = inode;
	dreq->bytes_left = dreq->max_count = count;
	dreq->io_start = pos;
	dreq->ctx = get_nfs_open_context(nfs_file_open_context(iocb->ki_filp));
	l_ctx = nfs_get_lock_context(dreq->ctx);
	if (IS_ERR(l_ctx)) {
		result = PTR_ERR(l_ctx);
		goto out_release;
	}
	dreq->l_ctx = l_ctx;
	if (!is_sync_kiocb(iocb))
		dreq->iocb = iocb;

	nfs_start_io_direct(inode);

	requested = nfs_direct_write_schedule_iovec(dreq, iter, pos);

	if (mapping->nrpages) {
		invalidate_inode_pages2_range(mapping,
					      pos >> PAGE_SHIFT, end);
	}

	nfs_end_io_direct(inode);

	if (requested > 0) {
		result = nfs_direct_wait(dreq);
		if (result > 0) {
			requested -= result;
			iocb->ki_pos = pos + result;
			/* XXX: should check the generic_write_sync retval */
			generic_write_sync(iocb, result);
		}
		iov_iter_revert(iter, requested);
	} else {
		result = requested;
	}
out_release:
	nfs_direct_req_release(dreq);
out:
	return result;
}