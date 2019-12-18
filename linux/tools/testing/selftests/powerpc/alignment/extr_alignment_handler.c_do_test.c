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
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PROT_WRITE ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int bufsize ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 void* mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int posix_memalign (void**,int,int) ; 
 int /*<<< orphan*/  preload_data (void*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int test_memcmp (void*,void*,int,int,char*) ; 
 int test_memcpy (void*,void*,int,int,void (*) (char*,char*)) ; 

int do_test(char *test_name, void (*test_func)(char *, char *))
{
	int offset, width, fd, rc, r;
	void *mem0, *mem1, *ci0, *ci1;

	printf("\tDoing %s:\t", test_name);

	fd = open("/dev/fb0", O_RDWR);
	if (fd < 0) {
		printf("\n");
		perror("Can't open /dev/fb0 now?");
		return 1;
	}

	ci0 = mmap(NULL, bufsize, PROT_WRITE, MAP_SHARED,
		   fd, 0x0);
	ci1 = mmap(NULL, bufsize, PROT_WRITE, MAP_SHARED,
		   fd, bufsize);
	if ((ci0 == MAP_FAILED) || (ci1 == MAP_FAILED)) {
		printf("\n");
		perror("mmap failed");
		SKIP_IF(1);
	}

	rc = posix_memalign(&mem0, bufsize, bufsize);
	if (rc) {
		printf("\n");
		return rc;
	}

	rc = posix_memalign(&mem1, bufsize, bufsize);
	if (rc) {
		printf("\n");
		free(mem0);
		return rc;
	}

	rc = 0;
	/* offset = 0 no alignment fault, so skip */
	for (offset = 1; offset < 16; offset++) {
		width = 16; /* vsx == 16 bytes */
		r = 0;

		/* load pattern into memory byte by byte */
		preload_data(ci0, offset, width);
		preload_data(mem0, offset, width); // FIXME: remove??
		memcpy(ci0, mem0, bufsize);
		memcpy(ci1, mem1, bufsize); /* initialise output to the same */

		/* sanity check */
		test_memcmp(mem0, ci0, width, offset, test_name);

		r |= test_memcpy(ci1,  ci0,  width, offset, test_func);
		r |= test_memcpy(mem1, mem0, width, offset, test_func);
		if (r && !debug) {
			printf("FAILED: Got signal");
			rc = 1;
			break;
		}

		r |= test_memcmp(mem1, ci1, width, offset, test_name);
		if (r && !debug) {
			printf("FAILED: Wrong Data");
			rc = 1;
			break;
		}
	}

	if (rc == 0)
		printf("PASSED");

	printf("\n");

	munmap(ci0, bufsize);
	munmap(ci1, bufsize);
	free(mem0);
	free(mem1);
	close(fd);

	return rc;
}