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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_sigaction; } ;
typedef  int off_t ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 char* file_name ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int run_test (void*,int) ; 
 int /*<<< orphan*/  segv ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscall_available () ; 

int test_file(void)
{
	struct sigaction act = {
		.sa_sigaction = segv,
		.sa_flags = SA_SIGINFO
	};
	void *fileblock;
	off_t filesize;
	int fd;

	SKIP_IF(!syscall_available());

	fd = open(file_name, O_RDWR);
	if (fd == -1) {
		perror("failed to open file");
		return 1;
	}
	sigaction(SIGSEGV, &act, NULL);

	filesize = lseek(fd, 0, SEEK_END);
	if (filesize & 0xffff)
		filesize &= ~0xfffful;

	fileblock = mmap(NULL, filesize, PROT_READ | PROT_WRITE,
			 MAP_SHARED, fd, 0);
	if (fileblock == MAP_FAILED) {
		perror("failed to map file");
		return 1;
	}
	printf("allocated %s for 0x%lx bytes at %p\n",
	       file_name, filesize, fileblock);

	printf("testing file map...\n");

	return run_test(fileblock, filesize);
}