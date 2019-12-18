#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iov_iter {int type; } ;
struct file {int f_flags; struct cifsFileInfo* private_data; } ;
struct cifs_tcon {TYPE_3__* ses; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_aio_ctx {int should_dirty; int direct_io; size_t len; int rc; int total_len; int /*<<< orphan*/  refcount; int /*<<< orphan*/  aio_mutex; int /*<<< orphan*/  done; int /*<<< orphan*/  list; struct iov_iter iter; int /*<<< orphan*/  pos; struct kiocb* iocb; int /*<<< orphan*/  cfile; } ;
struct cifsFileInfo {int /*<<< orphan*/  tlink; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {TYPE_2__* server; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  async_readv; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_FILE_SB (struct file*) ; 
 int EINTR ; 
 int EIOCBQUEUED ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FYI ; 
 int ITER_KVEC ; 
 int O_ACCMODE ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  cifsFileInfo_get (struct cifsFileInfo*) ; 
 struct cifs_aio_ctx* cifs_aio_ctx_alloc () ; 
 int /*<<< orphan*/  cifs_aio_ctx_release ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int cifs_send_async_read (int /*<<< orphan*/ ,size_t,struct cifsFileInfo*,struct cifs_sb_info*,int /*<<< orphan*/ *,struct cifs_aio_ctx*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 
 scalar_t__ iter_is_iovec (struct iov_iter*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int setup_aio_ctx_iter (struct cifs_aio_ctx*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 
 int wait_for_completion_killable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t __cifs_readv(
	struct kiocb *iocb, struct iov_iter *to, bool direct)
{
	size_t len;
	struct file *file = iocb->ki_filp;
	struct cifs_sb_info *cifs_sb;
	struct cifsFileInfo *cfile;
	struct cifs_tcon *tcon;
	ssize_t rc, total_read = 0;
	loff_t offset = iocb->ki_pos;
	struct cifs_aio_ctx *ctx;

	/*
	 * iov_iter_get_pages_alloc() doesn't work with ITER_KVEC,
	 * fall back to data copy read path
	 * this could be improved by getting pages directly in ITER_KVEC
	 */
	if (direct && to->type & ITER_KVEC) {
		cifs_dbg(FYI, "use non-direct cifs_user_readv for kvec I/O\n");
		direct = false;
	}

	len = iov_iter_count(to);
	if (!len)
		return 0;

	cifs_sb = CIFS_FILE_SB(file);
	cfile = file->private_data;
	tcon = tlink_tcon(cfile->tlink);

	if (!tcon->ses->server->ops->async_readv)
		return -ENOSYS;

	if ((file->f_flags & O_ACCMODE) == O_WRONLY)
		cifs_dbg(FYI, "attempting read on write only file instance\n");

	ctx = cifs_aio_ctx_alloc();
	if (!ctx)
		return -ENOMEM;

	ctx->cfile = cifsFileInfo_get(cfile);

	if (!is_sync_kiocb(iocb))
		ctx->iocb = iocb;

	if (iter_is_iovec(to))
		ctx->should_dirty = true;

	if (direct) {
		ctx->pos = offset;
		ctx->direct_io = true;
		ctx->iter = *to;
		ctx->len = len;
	} else {
		rc = setup_aio_ctx_iter(ctx, to, READ);
		if (rc) {
			kref_put(&ctx->refcount, cifs_aio_ctx_release);
			return rc;
		}
		len = ctx->len;
	}

	/* grab a lock here due to read response handlers can access ctx */
	mutex_lock(&ctx->aio_mutex);

	rc = cifs_send_async_read(offset, len, cfile, cifs_sb, &ctx->list, ctx);

	/* if at least one read request send succeeded, then reset rc */
	if (!list_empty(&ctx->list))
		rc = 0;

	mutex_unlock(&ctx->aio_mutex);

	if (rc) {
		kref_put(&ctx->refcount, cifs_aio_ctx_release);
		return rc;
	}

	if (!is_sync_kiocb(iocb)) {
		kref_put(&ctx->refcount, cifs_aio_ctx_release);
		return -EIOCBQUEUED;
	}

	rc = wait_for_completion_killable(&ctx->done);
	if (rc) {
		mutex_lock(&ctx->aio_mutex);
		ctx->rc = rc = -EINTR;
		total_read = ctx->total_len;
		mutex_unlock(&ctx->aio_mutex);
	} else {
		rc = ctx->rc;
		total_read = ctx->total_len;
	}

	kref_put(&ctx->refcount, cifs_aio_ctx_release);

	if (total_read) {
		iocb->ki_pos += total_read;
		return total_read;
	}
	return rc;
}