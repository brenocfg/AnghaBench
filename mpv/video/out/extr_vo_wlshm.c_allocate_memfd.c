#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  F_ADD_SEALS ; 
 int F_SEAL_SEAL ; 
 int F_SEAL_SHRINK ; 
 int MFD_ALLOW_SEALING ; 
 int MFD_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int memfd_create (char*,int) ; 
 scalar_t__ posix_fallocate (int,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int allocate_memfd(size_t size)
{
    int fd = memfd_create("mpv", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    if (fd < 0)
        return -1;

    fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);

    if (posix_fallocate(fd, 0, size) == 0)
        return fd;

    close(fd);
    return -1;
}