#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ result; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_file ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct rrdeng_jf_sb {int /*<<< orphan*/  version; int /*<<< orphan*/  magic_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  RRDENG_JF_MAGIC ; 
 int /*<<< orphan*/  RRDENG_JF_VER ; 
 int /*<<< orphan*/  RRDENG_MAGIC_SZ ; 
 int /*<<< orphan*/  RRDENG_VER_SZ ; 
 int /*<<< orphan*/  RRDFILE_ALIGNMENT ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rrdeng_jf_sb*) ; 
 int posix_memalign (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uv_buf_init (void*,int) ; 
 int uv_fs_read (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_strerror (int) ; 

__attribute__((used)) static int check_journal_file_superblock(uv_file file)
{
    int ret;
    struct rrdeng_jf_sb *superblock;
    uv_buf_t iov;
    uv_fs_t req;

    ret = posix_memalign((void *)&superblock, RRDFILE_ALIGNMENT, sizeof(*superblock));
    if (unlikely(ret)) {
        fatal("posix_memalign:%s", strerror(ret));
    }
    iov = uv_buf_init((void *)superblock, sizeof(*superblock));

    ret = uv_fs_read(NULL, &req, file, &iov, 1, 0, NULL);
    if (ret < 0) {
        error("uv_fs_read: %s", uv_strerror(ret));
        uv_fs_req_cleanup(&req);
        goto error;
    }
    assert(req.result >= 0);
    uv_fs_req_cleanup(&req);

    if (strncmp(superblock->magic_number, RRDENG_JF_MAGIC, RRDENG_MAGIC_SZ) ||
        strncmp(superblock->version, RRDENG_JF_VER, RRDENG_VER_SZ)) {
        error("File has invalid superblock.");
        ret = UV_EINVAL;
    } else {
        ret = 0;
    }
    error:
    free(superblock);
    return ret;
}