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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  mfd_def_size ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static void mfd_assert_read(int fd)
{
	char buf[16];
	void *p;
	ssize_t l;

	l = read(fd, buf, sizeof(buf));
	if (l != sizeof(buf)) {
		printf("read() failed: %m\n");
		abort();
	}

	/* verify PROT_READ *is* allowed */
	p = mmap(NULL,
		 mfd_def_size,
		 PROT_READ,
		 MAP_PRIVATE,
		 fd,
		 0);
	if (p == MAP_FAILED) {
		printf("mmap() failed: %m\n");
		abort();
	}
	munmap(p, mfd_def_size);

	/* verify MAP_PRIVATE is *always* allowed (even writable) */
	p = mmap(NULL,
		 mfd_def_size,
		 PROT_READ | PROT_WRITE,
		 MAP_PRIVATE,
		 fd,
		 0);
	if (p == MAP_FAILED) {
		printf("mmap() failed: %m\n");
		abort();
	}
	munmap(p, mfd_def_size);
}