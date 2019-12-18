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
struct TYPE_5__ {int io_write_bytes; int /*<<< orphan*/  io_write_requests; int /*<<< orphan*/  io_errors; int /*<<< orphan*/  datafile_creations; int /*<<< orphan*/  fs_errors; } ;
struct rrdengine_instance {TYPE_1__ stats; } ;
struct rrdengine_datafile {int pos; int /*<<< orphan*/  file; struct rrdengine_instance* ctx; } ;
struct rrdeng_df_sb {int tier; int /*<<< orphan*/  version; int /*<<< orphan*/  magic_number; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  RRDENG_DF_MAGIC ; 
 int /*<<< orphan*/  RRDENG_DF_VER ; 
 int /*<<< orphan*/  RRDENG_MAGIC_SZ ; 
 int RRDENG_PATH_MAX ; 
 int /*<<< orphan*/  RRDENG_VER_SZ ; 
 int /*<<< orphan*/  RRDFILE_ALIGNMENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destroy_data_file (struct rrdengine_datafile*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rrdeng_df_sb*) ; 
 int /*<<< orphan*/  generate_datafilepath (struct rrdengine_datafile*,char*,int) ; 
 int /*<<< orphan*/  global_fs_errors ; 
 int /*<<< orphan*/  global_io_errors ; 
 int open_file_direct_io (char*,int,int /*<<< orphan*/ *) ; 
 int posix_memalign (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rrd_stat_atomic_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uv_buf_init (void*,int) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_2__*) ; 
 int uv_fs_write (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_strerror (int) ; 

int create_data_file(struct rrdengine_datafile *datafile)
{
    struct rrdengine_instance *ctx = datafile->ctx;
    uv_fs_t req;
    uv_file file;
    int ret, fd;
    struct rrdeng_df_sb *superblock;
    uv_buf_t iov;
    char path[RRDENG_PATH_MAX];

    generate_datafilepath(datafile, path, sizeof(path));
    fd = open_file_direct_io(path, O_CREAT | O_RDWR | O_TRUNC, &file);
    if (fd < 0) {
        ++ctx->stats.fs_errors;
        rrd_stat_atomic_add(&global_fs_errors, 1);
        return fd;
    }
    datafile->file = file;
    ++ctx->stats.datafile_creations;

    ret = posix_memalign((void *)&superblock, RRDFILE_ALIGNMENT, sizeof(*superblock));
    if (unlikely(ret)) {
        fatal("posix_memalign:%s", strerror(ret));
    }
    (void) strncpy(superblock->magic_number, RRDENG_DF_MAGIC, RRDENG_MAGIC_SZ);
    (void) strncpy(superblock->version, RRDENG_DF_VER, RRDENG_VER_SZ);
    superblock->tier = 1;

    iov = uv_buf_init((void *)superblock, sizeof(*superblock));

    ret = uv_fs_write(NULL, &req, file, &iov, 1, 0, NULL);
    if (ret < 0) {
        assert(req.result < 0);
        error("uv_fs_write: %s", uv_strerror(ret));
        ++ctx->stats.io_errors;
        rrd_stat_atomic_add(&global_io_errors, 1);
    }
    uv_fs_req_cleanup(&req);
    free(superblock);
    if (ret < 0) {
        destroy_data_file(datafile);
        return ret;
    }

    datafile->pos = sizeof(*superblock);
    ctx->stats.io_write_bytes += sizeof(*superblock);
    ++ctx->stats.io_write_requests;

    return 0;
}