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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EPERM ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  abort () ; 
 int fallocate (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_def_size ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mprotect (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ write (int,char*,int) ; 

__attribute__((used)) static void mfd_fail_write(int fd)
{
	ssize_t l;
	void *p;
	int r;

	/* verify write() fails */
	l = write(fd, "data", 4);
	if (l != -EPERM) {
		printf("expected EPERM on write(), but got %d: %m\n", (int)l);
		abort();
	}

	/* verify PROT_READ | PROT_WRITE is not allowed */
	p = mmap(NULL,
		 mfd_def_size,
		 PROT_READ | PROT_WRITE,
		 MAP_SHARED,
		 fd,
		 0);
	if (p != MAP_FAILED) {
		printf("mmap() didn't fail as expected\n");
		abort();
	}

	/* verify PROT_WRITE is not allowed */
	p = mmap(NULL,
		 mfd_def_size,
		 PROT_WRITE,
		 MAP_SHARED,
		 fd,
		 0);
	if (p != MAP_FAILED) {
		printf("mmap() didn't fail as expected\n");
		abort();
	}

	/* Verify PROT_READ with MAP_SHARED with a following mprotect is not
	 * allowed. Note that for r/w the kernel already prevents the mmap. */
	p = mmap(NULL,
		 mfd_def_size,
		 PROT_READ,
		 MAP_SHARED,
		 fd,
		 0);
	if (p != MAP_FAILED) {
		r = mprotect(p, mfd_def_size, PROT_READ | PROT_WRITE);
		if (r >= 0) {
			printf("mmap()+mprotect() didn't fail as expected\n");
			abort();
		}
	}

	/* verify PUNCH_HOLE fails */
	r = fallocate(fd,
		      FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE,
		      0,
		      mfd_def_size);
	if (r >= 0) {
		printf("fallocate(PUNCH_HOLE) didn't fail as expected\n");
		abort();
	}
}