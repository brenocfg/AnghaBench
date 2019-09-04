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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCIIOC_MMAP_IS_MEM ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fnmatch (char*,char*,int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int munmap (void*,size_t) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sum ; 

__attribute__((used)) static int map_mem(char *path, off_t offset, size_t length, int touch)
{
	int fd, rc;
	void *addr;
	int *c;

	fd = open(path, O_RDWR);
	if (fd == -1) {
		perror(path);
		return -1;
	}

	if (fnmatch("/proc/bus/pci/*", path, 0) == 0) {
		rc = ioctl(fd, PCIIOC_MMAP_IS_MEM);
		if (rc == -1)
			perror("PCIIOC_MMAP_IS_MEM ioctl");
	}

	addr = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, offset);
	if (addr == MAP_FAILED)
		return 1;

	if (touch) {
		c = (int *) addr;
		while (c < (int *) (addr + length))
			sum += *c++;
	}

	rc = munmap(addr, length);
	if (rc == -1) {
		perror("munmap");
		return -1;
	}

	close(fd);
	return 0;
}