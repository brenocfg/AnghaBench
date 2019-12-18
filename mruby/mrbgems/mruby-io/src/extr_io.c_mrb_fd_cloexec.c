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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mrb_bug (int /*<<< orphan*/ *,char*,int,int,...) ; 

__attribute__((used)) static void
mrb_fd_cloexec(mrb_state *mrb, int fd)
{
#if defined(F_GETFD) && defined(F_SETFD) && defined(FD_CLOEXEC)
  int flags, flags2;

  flags = fcntl(fd, F_GETFD);
  if (flags == -1) {
    mrb_bug(mrb, "mrb_fd_cloexec: fcntl(%d, F_GETFD) failed: %d", fd, errno);
  }
  if (fd <= 2) {
    flags2 = flags & ~FD_CLOEXEC; /* Clear CLOEXEC for standard file descriptors: 0, 1, 2. */
  }
  else {
    flags2 = flags | FD_CLOEXEC; /* Set CLOEXEC for non-standard file descriptors: 3, 4, 5, ... */
  }
  if (flags != flags2) {
    if (fcntl(fd, F_SETFD, flags2) == -1) {
      mrb_bug(mrb, "mrb_fd_cloexec: fcntl(%d, F_SETFD, %d) failed: %d", fd, flags2, errno);
    }
  }
#endif
}