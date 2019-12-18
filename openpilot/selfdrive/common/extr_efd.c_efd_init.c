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
struct timespec {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct kevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFD_CLOEXEC ; 
 int /*<<< orphan*/  EVENT_IDENT ; 
 int /*<<< orphan*/  EVFILT_USER ; 
 int EV_ADD ; 
 int EV_CLEAR ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int eventfd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kevent (int,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec*) ; 
 int kqueue () ; 

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