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
struct TYPE_2__ {scalar_t__* __val; } ;
struct statfs {TYPE_1__ f_fsid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int statfs (char const*,struct statfs*) ; 

__attribute__((used)) static int is_virtual_filesystem(const char *path, char **reason) {

#if defined(__APPLE__) || defined(__FreeBSD__)
    (void)path;
    (void)reason;
#else
    struct statfs stat;
    // stat.f_fsid.__val[0] is a file system id
    // stat.f_fsid.__val[1] is the inode
    // so their combination uniquely identifies the file/dir

    if (statfs(path, &stat) == -1) {
        if(reason) *reason = "failed to statfs()";
        return -1;
    }

    if(stat.f_fsid.__val[0] != 0 || stat.f_fsid.__val[1] != 0) {
        errno = EINVAL;
        if(reason) *reason = "is not a virtual file system";
        return -1;
    }
#endif

    return 0;
}