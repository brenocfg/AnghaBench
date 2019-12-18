#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct rrdengine_worker_config {int /*<<< orphan*/  loop; struct rrdengine_instance* ctx; } ;
struct rrdengine_journalfile {int /*<<< orphan*/  pos; int /*<<< orphan*/  file; } ;
struct TYPE_9__ {int /*<<< orphan*/  io_write_requests; int /*<<< orphan*/  io_write_bytes; } ;
struct TYPE_8__ {unsigned int buf_pos; unsigned int buf_size; int /*<<< orphan*/ * buf; } ;
struct TYPE_7__ {TYPE_1__* last; } ;
struct rrdengine_instance {TYPE_4__ stats; TYPE_3__ commit_log; int /*<<< orphan*/  disk_space; TYPE_2__ datafiles; } ;
struct TYPE_10__ {struct generic_io_descriptor* data; } ;
struct generic_io_descriptor {unsigned int bytes; int /*<<< orphan*/  iov; TYPE_5__ req; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * completion; int /*<<< orphan*/  pos; } ;
struct TYPE_6__ {struct rrdengine_journalfile* journalfile; } ;

/* Variables and functions */
 scalar_t__ RRDENG_BLOCK_SIZE ; 
 int /*<<< orphan*/  STORE_PADDING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  flush_transaction_buffer_cb ; 
 struct generic_io_descriptor* mallocz (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uv_buf_init (void*,unsigned int) ; 
 int uv_fs_write (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wal_flush_transaction_buffer(struct rrdengine_worker_config* wc)
{
    struct rrdengine_instance *ctx = wc->ctx;
    int ret;
    struct generic_io_descriptor *io_descr;
    unsigned pos, size;
    struct rrdengine_journalfile *journalfile;

    if (unlikely(NULL == ctx->commit_log.buf || 0 == ctx->commit_log.buf_pos)) {
        return;
    }
    /* care with outstanding transactions when switching journal files */
    journalfile = ctx->datafiles.last->journalfile;

    io_descr = mallocz(sizeof(*io_descr));
    pos = ctx->commit_log.buf_pos;
    size = ctx->commit_log.buf_size;
    if (pos < size) {
        /* simulate an empty transaction to skip the rest of the block */
        *(uint8_t *) (ctx->commit_log.buf + pos) = STORE_PADDING;
    }
    io_descr->buf = ctx->commit_log.buf;
    io_descr->bytes = size;
    io_descr->pos = journalfile->pos;
    io_descr->req.data = io_descr;
    io_descr->completion = NULL;

    io_descr->iov = uv_buf_init((void *)io_descr->buf, size);
    ret = uv_fs_write(wc->loop, &io_descr->req, journalfile->file, &io_descr->iov, 1,
                      journalfile->pos, flush_transaction_buffer_cb);
    assert (-1 != ret);
    journalfile->pos += RRDENG_BLOCK_SIZE;
    ctx->disk_space += RRDENG_BLOCK_SIZE;
    ctx->commit_log.buf = NULL;
    ctx->stats.io_write_bytes += RRDENG_BLOCK_SIZE;
    ++ctx->stats.io_write_requests;
}