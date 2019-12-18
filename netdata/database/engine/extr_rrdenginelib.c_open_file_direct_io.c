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
typedef  scalar_t__ uv_file ;

/* Variables and functions */
 int /*<<< orphan*/  F_NOCACHE ; 
 int O_DIRECT ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 int uv_fs_open (int /*<<< orphan*/ *,TYPE_1__*,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_req_cleanup (TYPE_1__*) ; 

int open_file_direct_io(char *path, int flags, uv_file *file)
{
    uv_fs_t req;
    int fd, current_flags, direct;

    for (direct = 1 ; direct >= 0 ; --direct) {
#ifdef __APPLE__
        /* Apple OS does not support O_DIRECT */
        direct = 0;
#endif
        current_flags = flags;
        if (direct) {
            current_flags |= O_DIRECT;
        }
        fd = uv_fs_open(NULL, &req, path, current_flags, S_IRUSR | S_IWUSR, NULL);
        if (fd < 0) {
            if ((direct) && (UV_EINVAL == fd)) {
                error("File \"%s\" does not support direct I/O, falling back to buffered I/O.", path);
            } else {
                error("Failed to open file \"%s\".", path);
                --direct; /* break the loop */
            }
        } else {
            assert(req.result >= 0);
            *file = req.result;
#ifdef __APPLE__
            info("Disabling OS X caching for file \"%s\".", path);
            fcntl(fd, F_NOCACHE, 1);
#endif
            --direct; /* break the loop */
        }
        uv_fs_req_cleanup(&req);
    }

    return fd;
}