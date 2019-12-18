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
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PFUNC () ; 
 int /*<<< orphan*/  dprintf (int,char*,char*) ; 
 int errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strerror_r (int,char*,int) ; 

__attribute__((used)) static int wait_data(int readfd) {
	PFUNC();
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(readfd, &fds);
	int ret;
	while((ret = select(readfd+1, &fds, NULL, NULL, NULL)) <= 0) {
		if(ret < 0) {
			int e = errno;
			if(e == EINTR) continue;
#ifdef __GLIBC__
			char emsg[1024];
			char* x = strerror_r(errno, emsg, sizeof emsg);
			dprintf(2, "select2: %s\n", x);
#endif
			return 0;
		}
	}
	return 1;
}