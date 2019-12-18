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
struct udmabuf_create {int memfd; int offset; int size; } ;
typedef  void* off_t ;
typedef  int /*<<< orphan*/  create ;

/* Variables and functions */
 int /*<<< orphan*/  F_ADD_SEALS ; 
 int /*<<< orphan*/  F_SEAL_SHRINK ; 
 int /*<<< orphan*/  MFD_ALLOW_SEALING ; 
 int NUM_PAGES ; 
 int /*<<< orphan*/  O_RDWR ; 
 char* TEST_PREFIX ; 
 int /*<<< orphan*/  UDMABUF_CREATE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int ftruncate (int,void*) ; 
 int getpagesize () ; 
 int ioctl (int,int /*<<< orphan*/ ,struct udmabuf_create*) ; 
 int memfd_create (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct udmabuf_create*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
	struct udmabuf_create create;
	int devfd, memfd, buf, ret;
	off_t size;
	void *mem;

	devfd = open("/dev/udmabuf", O_RDWR);
	if (devfd < 0) {
		printf("%s: [skip,no-udmabuf]\n", TEST_PREFIX);
		exit(77);
	}

	memfd = memfd_create("udmabuf-test", MFD_ALLOW_SEALING);
	if (memfd < 0) {
		printf("%s: [skip,no-memfd]\n", TEST_PREFIX);
		exit(77);
	}

	ret = fcntl(memfd, F_ADD_SEALS, F_SEAL_SHRINK);
	if (ret < 0) {
		printf("%s: [skip,fcntl-add-seals]\n", TEST_PREFIX);
		exit(77);
	}


	size = getpagesize() * NUM_PAGES;
	ret = ftruncate(memfd, size);
	if (ret == -1) {
		printf("%s: [FAIL,memfd-truncate]\n", TEST_PREFIX);
		exit(1);
	}

	memset(&create, 0, sizeof(create));

	/* should fail (offset not page aligned) */
	create.memfd  = memfd;
	create.offset = getpagesize()/2;
	create.size   = getpagesize();
	buf = ioctl(devfd, UDMABUF_CREATE, &create);
	if (buf >= 0) {
		printf("%s: [FAIL,test-1]\n", TEST_PREFIX);
		exit(1);
	}

	/* should fail (size not multiple of page) */
	create.memfd  = memfd;
	create.offset = 0;
	create.size   = getpagesize()/2;
	buf = ioctl(devfd, UDMABUF_CREATE, &create);
	if (buf >= 0) {
		printf("%s: [FAIL,test-2]\n", TEST_PREFIX);
		exit(1);
	}

	/* should fail (not memfd) */
	create.memfd  = 0; /* stdin */
	create.offset = 0;
	create.size   = size;
	buf = ioctl(devfd, UDMABUF_CREATE, &create);
	if (buf >= 0) {
		printf("%s: [FAIL,test-3]\n", TEST_PREFIX);
		exit(1);
	}

	/* should work */
	create.memfd  = memfd;
	create.offset = 0;
	create.size   = size;
	buf = ioctl(devfd, UDMABUF_CREATE, &create);
	if (buf < 0) {
		printf("%s: [FAIL,test-4]\n", TEST_PREFIX);
		exit(1);
	}

	fprintf(stderr, "%s: ok\n", TEST_PREFIX);
	close(buf);
	close(memfd);
	close(devfd);
	return 0;
}