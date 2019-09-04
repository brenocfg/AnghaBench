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
 int /*<<< orphan*/  ADDR ; 
 int /*<<< orphan*/  FILE_NAME ; 
 int /*<<< orphan*/  FLAGS ; 
 int /*<<< orphan*/  LENGTH ; 
 void* MAP_FAILED ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PROTECTION ; 
 int /*<<< orphan*/  check_bytes (void*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,void*) ; 
 int read_bytes (void*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_bytes (void*) ; 

int main(void)
{
	void *addr;
	int fd, ret;

	fd = open(FILE_NAME, O_CREAT | O_RDWR, 0755);
	if (fd < 0) {
		perror("Open failed");
		exit(1);
	}

	addr = mmap(ADDR, LENGTH, PROTECTION, FLAGS, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		unlink(FILE_NAME);
		exit(1);
	}

	printf("Returned address is %p\n", addr);
	check_bytes(addr);
	write_bytes(addr);
	ret = read_bytes(addr);

	munmap(addr, LENGTH);
	close(fd);
	unlink(FILE_NAME);

	return ret;
}