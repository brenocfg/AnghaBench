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
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  abort () ; 
 int ftruncate (int,int) ; 
 int mfd_def_size ; 
 int /*<<< orphan*/  mfd_fail_open (int,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void mfd_fail_shrink(int fd)
{
	int r;

	r = ftruncate(fd, mfd_def_size / 2);
	if (r >= 0) {
		printf("ftruncate(SHRINK) didn't fail as expected\n");
		abort();
	}

	mfd_fail_open(fd,
		      O_RDWR | O_CREAT | O_TRUNC,
		      S_IRUSR | S_IWUSR);
}