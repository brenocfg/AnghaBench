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
struct nfs_lock_context {int dummy; } ;
struct nfs_direct_req {size_t bytes_left; size_t max_count; int /*<<< orphan*/  flags; struct kiocb* iocb; struct nfs_lock_context* l_ctx; int /*<<< orphan*/  ctx; scalar_t__ io_start; struct inode* inode; } ;
struct kiocb {scalar_t__ ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  read_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FILE ; 
 scalar_t__ IS_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  NFSIOS_DIRECTREADBYTES ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_ODIRECT_SHOULD_DIRTY ; 
 int /*<<< orphan*/  PTR_ERR (struct nfs_lock_context*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct file*,size_t,long long) ; 
 int /*<<< orphan*/  get_nfs_open_context (int /*<<< orphan*/ ) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_revert (struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 
 scalar_t__ iter_is_iovec (struct iov_iter*) ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nfs_direct_read_schedule_iovec (struct nfs_direct_req*,struct iov_iter*,scalar_t__) ; 
 struct nfs_direct_req* nfs_direct_req_alloc () ; 
 int /*<<< orphan*/  nfs_direct_req_release (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_direct_wait (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_end_io_direct (struct inode*) ; 
 int /*<<< orphan*/  nfs_file_open_context (struct file*) ; 
 struct nfs_lock_context* nfs_get_lock_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_start_io_direct (struct inode*) ; 
 int /*<<< orphan*/  task_io_account_read (size_t) ; 

ssize_t nfs_file_direct_read(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	struct inode *inode = mapping->host;
	struct nfs_direct_req *dreq;
	struct nfs_lock_context *l_ctx;
	ssize_t result = -EINVAL, requested;
	size_t count = iov_iter_count(iter);
	nfs_add_stats(mapping->host, NFSIOS_DIRECTREADBYTES, count);

	dfprintk(FILE, "NFS: direct read(%pD2, %zd@%Ld)\n",
		file, count, (long long) iocb->ki_pos);

	result = 0;
	if (!count)
		goto out;

	task_io_account_read(count);

	result = -ENOMEM;
	dreq = nfs_direct_req_alloc();
	if (dreq == NULL)
		goto out;

	dreq->inode = inode;
	dreq->bytes_left = dreq->max_count = count;
	dreq->io_start = iocb->ki_pos;
	dreq->ctx = get_nfs_open_context(nfs_file_open_context(iocb->ki_filp));
	l_ctx = nfs_get_lock_context(dreq->ctx);
	if (IS_ERR(l_ctx)) {
		result = PTR_ERR(l_ctx);
		goto out_release;
	}
	dreq->l_ctx = l_ctx;
	if (!is_sync_kiocb(iocb))
		dreq->iocb = iocb;

	if (iter_is_iovec(iter))
		dreq->flags = NFS_ODIRECT_SHOULD_DIRTY;

	nfs_start_io_direct(inode);

	NFS_I(inode)->read_io += count;
	requested = nfs_direct_read_schedule_iovec(dreq, iter, iocb->ki_pos);

	nfs_end_io_direct(inode);

	if (requested > 0) {
		result = nfs_direct_wait(dreq);
		if (result > 0) {
			requested -= result;
			iocb->ki_pos += result;
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