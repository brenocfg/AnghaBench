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
struct TYPE_5__ {int st_mode; size_t st_size; } ;
typedef  TYPE_1__ uv_stat_t ;
struct TYPE_6__ {scalar_t__ result; TYPE_1__* ptr; } ;
typedef  TYPE_2__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_file ;
typedef  size_t uint64_t ;

/* Variables and functions */
 int S_IFREG ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int uv_fs_fstat (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  uv_strerror (int) ; 

int check_file_properties(uv_file file, uint64_t *file_size, size_t min_size)
{
    int ret;
    uv_fs_t req;
    uv_stat_t* s;

    ret = uv_fs_fstat(NULL, &req, file, NULL);
    if (ret < 0) {
        fatal("uv_fs_fstat: %s\n", uv_strerror(ret));
    }
    assert(req.result == 0);
    s = req.ptr;
    if (!(s->st_mode & S_IFREG)) {
        error("Not a regular file.\n");
        uv_fs_req_cleanup(&req);
        return UV_EINVAL;
    }
    if (s->st_size < min_size) {
        error("File length is too short.\n");
        uv_fs_req_cleanup(&req);
        return UV_EINVAL;
    }
    *file_size = s->st_size;
    uv_fs_req_cleanup(&req);

    return 0;
}