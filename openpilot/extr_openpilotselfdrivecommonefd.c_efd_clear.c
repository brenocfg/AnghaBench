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
typedef  int /*<<< orphan*/  eventfd_t ;

/* Variables and functions */
 int /*<<< orphan*/  eventfd_read (int,int /*<<< orphan*/ *) ; 

void efd_clear(int fd) {
#ifdef __linux__
  eventfd_t efd_cnt;
  eventfd_read(fd, &efd_cnt);
#else
  struct kevent kev;
  struct timespec timeout = {0, 0};
  int nfds = kevent(fd, NULL, 0, &kev, 1, &timeout);
  assert(nfds != -1);
#endif
}