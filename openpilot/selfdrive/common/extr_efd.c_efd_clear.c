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
typedef  int /*<<< orphan*/  eventfd_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  eventfd_read (int,int /*<<< orphan*/ *) ; 
 int kevent (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,struct timespec*) ; 

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