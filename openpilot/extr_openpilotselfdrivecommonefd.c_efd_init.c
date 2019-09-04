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
 int /*<<< orphan*/  EFD_CLOEXEC ; 
 int eventfd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int efd_init() {
#ifdef __linux__
  return eventfd(0, EFD_CLOEXEC);
#else
  int fd = kqueue();
  assert(fd >= 0);

  struct kevent kev;
  EV_SET(&kev, EVENT_IDENT, EVFILT_USER, EV_ADD | EV_CLEAR, 0, 0, NULL);

  struct timespec timeout = {0, 0};
  int err = kevent(fd, &kev, 1, NULL, 0, &timeout);
  assert(err != -1);

  return fd;
#endif
}