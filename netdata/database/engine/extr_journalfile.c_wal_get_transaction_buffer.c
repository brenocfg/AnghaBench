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
struct rrdengine_worker_config {struct rrdengine_instance* ctx; } ;
struct TYPE_2__ {void* buf; unsigned int buf_pos; unsigned int buf_size; } ;
struct rrdengine_instance {TYPE_1__ commit_log; } ;

/* Variables and functions */
 unsigned int ALIGN_BYTES_CEILING (unsigned int) ; 
 int /*<<< orphan*/  RRDFILE_ALIGNMENT ; 
 int /*<<< orphan*/  assert (unsigned int) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int posix_memalign (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wal_flush_transaction_buffer (struct rrdengine_worker_config*) ; 

void * wal_get_transaction_buffer(struct rrdengine_worker_config* wc, unsigned size)
{
    struct rrdengine_instance *ctx = wc->ctx;
    int ret;
    unsigned buf_pos, buf_size;

    assert(size);
    if (ctx->commit_log.buf) {
        unsigned remaining;

        buf_pos = ctx->commit_log.buf_pos;
        buf_size = ctx->commit_log.buf_size;
        remaining = buf_size - buf_pos;
        if (size > remaining) {
            /* we need a new buffer */
            wal_flush_transaction_buffer(wc);
        }
    }
    if (NULL == ctx->commit_log.buf) {
        buf_size = ALIGN_BYTES_CEILING(size);
        ret = posix_memalign((void *)&ctx->commit_log.buf, RRDFILE_ALIGNMENT, buf_size);
        if (unlikely(ret)) {
            fatal("posix_memalign:%s", strerror(ret));
        }
        buf_pos = ctx->commit_log.buf_pos = 0;
        ctx->commit_log.buf_size =  buf_size;
    }
    ctx->commit_log.buf_pos += size;

    return ctx->commit_log.buf + buf_pos;
}