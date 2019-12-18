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
 int FLAGS ; 
 size_t LENGTH ; 
 void* MAP_FAILED ; 
 int MAP_HUGE_MASK ; 
 int MAP_HUGE_SHIFT ; 
 int /*<<< orphan*/  PROTECTION ; 
 int atoi (char*) ; 
 int atol (char*) ; 
 int /*<<< orphan*/  check_bytes (void*) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* mmap (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (void*,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_bytes (void*) ; 
 int /*<<< orphan*/  write_bytes (void*) ; 

int main(int argc, char **argv)
{
	void *addr;
	int ret;
	size_t length = LENGTH;
	int flags = FLAGS;
	int shift = 0;

	if (argc > 1)
		length = atol(argv[1]) << 20;
	if (argc > 2) {
		shift = atoi(argv[2]);
		if (shift)
			flags |= (shift & MAP_HUGE_MASK) << MAP_HUGE_SHIFT;
	}

	if (shift)
		printf("%u kB hugepages\n", 1 << shift);
	else
		printf("Default size hugepages\n");
	printf("Mapping %lu Mbytes\n", (unsigned long)length >> 20);

	addr = mmap(ADDR, length, PROTECTION, flags, -1, 0);
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