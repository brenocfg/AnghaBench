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
struct file {struct cifsFileInfo* private_data; } ;
struct cifs_tcon {TYPE_3__* ses; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_aio_ctx {int direct_io; size_t len; int rc; int total_len; int /*<<< orphan*/  refcount; int /*<<< orphan*/  aio_mutex; int /*<<< orphan*/  done; int /*<<< orphan*/  list; struct iov_iter iter; int /*<<< orphan*/  pos; struct kiocb* iocb; int /*<<< orphan*/  cfile; } ;
struct cifsFileInfo {int /*<<< orphan*/  tlink; } ;
typedef  int ssize_t ;
struct TYPE_6__ {TYPE_2__* server; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  async_writev; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_FILE_SB (struct file*) ; 
 int EINTR ; 
 int EIOCBQUEUED ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FYI ; 
 int ITER_KVEC ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  cifsFileInfo_get (struct cifsFileInfo*) ; 
 struct cifs_aio_ctx* cifs_aio_ctx_alloc () ; 
 int /*<<< orphan*/  cifs_aio_ctx_release ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int cifs_write_from_iter (int /*<<< orphan*/ ,size_t,struct iov_iter*,struct cifsFileInfo*,struct cifs_sb_info*,int /*<<< orphan*/ *,struct cifs_aio_ctx*) ; 
 int generic_write_checks (struct kiocb*,struct iov_iter*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int setup_aio_ctx_iter (struct cifs_aio_ctx*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int wait_for_completion_killable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t __cifs_writev(
	struct kiocb *iocb, struct iov_iter *from, bool direct)
{
	struct file *file = iocb->ki_filp;
	ssize_t total_written = 0;
	struct cifsFileInfo *cfile;
	struct cifs_tcon *tcon;
	struct cifs_sb_info *cifs_sb;
	struct cifs_aio_ctx *ctx;
	struct iov_iter saved_from = *from;
	size_t len = iov_iter_count(from);
	int rc;

	/*
	 * iov_iter_get_pages_alloc doesn't work with ITER_KVEC.
	 * In this case, fall back to non-direct write function.
	 * this could be improved by getting pages directly in ITER_KVEC
	 */
	if (direct && from->type & ITER_KVEC) {
		cifs_dbg(FYI, "use non-direct cifs_writev for kvec I/O\n");
		direct = false;
	}

	rc = generic_write_checks(iocb, from);
	if (rc <= 0)
		return rc;

	cifs_sb = CIFS_FILE_SB(file);
	cfile = file->private_data;
	tcon = tlink_tcon(cfile->tlink);

	if (!tcon->ses->server->ops->async_writev)
		return -ENOSYS;

	ctx = cifs_aio_ctx_alloc();
	if (!ctx)
		return -ENOMEM;

	ctx->cfile = cifsFileInfo_get(cfile);

	if (!is_sync_kiocb(iocb))
		ctx->iocb = iocb;

	ctx->pos = iocb->ki_pos;

	if (direct) {
		ctx->direct_io = true;
		ctx->iter = *from;
		ctx->len = len;
	} else {
		rc = setup_aio_ctx_iter(ctx, from, WRITE);
		if (rc) {
			kref_put(&ctx->refcount, cifs_aio_ctx_release);
			return rc;
		}
	}

	/* grab a lock here due to read response handlers can access ctx */
	mutex_lock(&ctx->aio_mutex);

	rc = cifs_write_from_iter(iocb->ki_pos, ctx->len, &saved_from,
				  cfile, cifs_sb, &ctx->list, ctx);

	/*
	 * If at least one write was successfully sent, then discard any rc
	 * value from the later writes. If the other write succeeds, then
	 * we'll end up returning whatever was written. If it fails, then
	 * we'll get a new rc value from that.
	 */
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
		total_written = ctx->total_len;
		mutex_unlock(&ctx->aio_mutex);
	} else {
		rc = ctx->rc;
		total_written = ctx->total_len;
	}

	kref_put(&ctx->refcount, cifs_aio_ctx_release);

	if (unlikely(!total_written))
		return rc;

	iocb->ki_pos += total_written;
	return total_written;
}