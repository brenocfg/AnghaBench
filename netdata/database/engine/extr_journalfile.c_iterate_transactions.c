#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ result; } ;
typedef  TYPE_2__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_file ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  unsigned int uint64_t ;
struct rrdengine_journalfile {unsigned int pos; int /*<<< orphan*/  file; } ;
struct TYPE_5__ {unsigned int io_read_bytes; int /*<<< orphan*/  io_read_requests; } ;
struct rrdengine_instance {TYPE_1__ stats; } ;
struct rrdeng_jf_sb {int dummy; } ;

/* Variables and functions */
 unsigned int ALIGN_BYTES_FLOOR (scalar_t__) ; 
 unsigned int MAX (unsigned int,unsigned int) ; 
 unsigned int MIN (scalar_t__,unsigned int) ; 
 scalar_t__ READAHEAD_BYTES ; 
 scalar_t__ RRDENG_BLOCK_SIZE ; 
 int /*<<< orphan*/  RRDFILE_ALIGNMENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int posix_memalign (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int replay_transaction (struct rrdengine_instance*,struct rrdengine_journalfile*,void*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uv_buf_init (void*,unsigned int) ; 
 int uv_fs_read (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  uv_strerror (int) ; 

__attribute__((used)) static uint64_t iterate_transactions(struct rrdengine_instance *ctx, struct rrdengine_journalfile *journalfile)
{
    uv_file file;
    uint64_t file_size;//, data_file_size;
    int ret;
    uint64_t pos, pos_i, max_id, id;
    unsigned size_bytes;
    void *buf;
    uv_buf_t iov;
    uv_fs_t req;

    file = journalfile->file;
    file_size = journalfile->pos;
    //data_file_size = journalfile->datafile->pos; TODO: utilize this?

    max_id = 1;
    ret = posix_memalign((void *)&buf, RRDFILE_ALIGNMENT, READAHEAD_BYTES);
    if (unlikely(ret)) {
        fatal("posix_memalign:%s", strerror(ret));
    }

    for (pos = sizeof(struct rrdeng_jf_sb) ; pos < file_size ; pos += READAHEAD_BYTES) {
        size_bytes = MIN(READAHEAD_BYTES, file_size - pos);
        iov = uv_buf_init(buf, size_bytes);
        ret = uv_fs_read(NULL, &req, file, &iov, 1, pos, NULL);
        if (ret < 0) {
            fatal("uv_fs_read: %s", uv_strerror(ret));
            /*uv_fs_req_cleanup(&req);*/
        }
        assert(req.result >= 0);
        uv_fs_req_cleanup(&req);
        ctx->stats.io_read_bytes += size_bytes;
        ++ctx->stats.io_read_requests;

        //pos_i = pos;
        //while (pos_i < pos + size_bytes) {
        for (pos_i = 0 ; pos_i < size_bytes ; ) {
            unsigned max_size;

            max_size = pos + size_bytes - pos_i;
            ret = replay_transaction(ctx, journalfile, buf + pos_i, &id, max_size);
            if (!ret) /* TODO: support transactions bigger than 4K */
                /* unknown transaction size, move on to the next block */
                pos_i = ALIGN_BYTES_FLOOR(pos_i + RRDENG_BLOCK_SIZE);
            else
                pos_i += ret;
            max_id = MAX(max_id, id);
        }
    }

    free(buf);
    return max_id;
}