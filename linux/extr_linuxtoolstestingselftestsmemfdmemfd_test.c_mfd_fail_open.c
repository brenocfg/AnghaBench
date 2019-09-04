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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void mfd_fail_open(int fd, int flags, mode_t mode)
{
	char buf[512];
	int r;

	sprintf(buf, "/proc/self/fd/%d", fd);
	r = open(buf, flags, mode);
	if (r >= 0) {
		printf("open(%s) didn't fail as expected\n", buf);
		abort();
	}
}