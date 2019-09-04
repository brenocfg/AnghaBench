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
 int /*<<< orphan*/  FLAGS ; 
 int /*<<< orphan*/  LENGTH ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  PROTECTION ; 
 int /*<<< orphan*/  check_bytes (void*) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,void*) ; 
 int read_bytes (void*) ; 
 int /*<<< orphan*/  write_bytes (void*) ; 

int main(void)
{
	void *addr;
	int ret;

	addr = mmap(ADDR, LENGTH, PROTECTION, FLAGS, -1, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	printf("Returned address is %p\n", addr);
	check_bytes(addr);
	write_bytes(addr);
	ret = read_bytes(addr);

	/* munmap() length of MAP_HUGETLB memory must be hugepage aligned */
	if (munmap(addr, LENGTH)) {
		perror("munmap");
		exit(1);
	}

	return ret;
}