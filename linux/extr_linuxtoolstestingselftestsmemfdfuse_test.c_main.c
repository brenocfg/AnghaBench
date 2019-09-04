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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int F_SEAL_WRITE ; 
 int MFD_ALLOW_SEALING ; 
 int MFD_CLOEXEC ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  abort () ; 
 char* calloc (int,unsigned long) ; 
 int /*<<< orphan*/  close (int) ; 
 unsigned long default_huge_page_size () ; 
 int /*<<< orphan*/  free (char*) ; 
 int global_mfd ; 
 void* global_p ; 
 int hugetlbfs_test ; 
 int /*<<< orphan*/  join_sealing_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (void*,char*,unsigned long) ; 
 int mfd_assert_get_seals (int) ; 
 int /*<<< orphan*/  mfd_assert_has_seals (int,int) ; 
 void* mfd_assert_mmap_private (int) ; 
 void* mfd_assert_mmap_shared (int) ; 
 int mfd_assert_new (char*,unsigned long,int) ; 
 unsigned long mfd_def_size ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,void*,unsigned long) ; 
 int /*<<< orphan*/  spawn_sealing_thread () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int main(int argc, char **argv)
{
	char *zero;
	int fd, mfd, r;
	void *p;
	int was_sealed;
	pid_t pid;

	if (argc < 2) {
		printf("error: please pass path to file in fuse_mnt mount-point\n");
		abort();
	}

	if (argc >= 3) {
		if (!strcmp(argv[2], "hugetlbfs")) {
			unsigned long hpage_size = default_huge_page_size();

			if (!hpage_size) {
				printf("Unable to determine huge page size\n");
				abort();
			}

			hugetlbfs_test = 1;
			mfd_def_size = hpage_size * 2;
		} else {
			printf("Unknown option: %s\n", argv[2]);
			abort();
		}
	}

	zero = calloc(sizeof(*zero), mfd_def_size);

	/* open FUSE memfd file for GUP testing */
	printf("opening: %s\n", argv[1]);
	fd = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		printf("cannot open(\"%s\"): %m\n", argv[1]);
		abort();
	}

	/* create new memfd-object */
	mfd = mfd_assert_new("kern_memfd_fuse",
			     mfd_def_size,
			     MFD_CLOEXEC | MFD_ALLOW_SEALING);

	/* mmap memfd-object for writing */
	p = mfd_assert_mmap_shared(mfd);

	/* pass mfd+mapping to a separate sealing-thread which tries to seal
	 * the memfd objects with SEAL_WRITE while we write into it */
	global_mfd = mfd;
	global_p = p;
	pid = spawn_sealing_thread();

	/* Use read() on the FUSE file to read into our memory-mapped memfd
	 * object. This races the other thread which tries to seal the
	 * memfd-object.
	 * If @fd is on the memfd-fake-FUSE-FS, the read() is delayed by 1s.
	 * This guarantees that the receive-buffer is pinned for 1s until the
	 * data is written into it. The racing ADD_SEALS should thus fail as
	 * the pages are still pinned. */
	r = read(fd, p, mfd_def_size);
	if (r < 0) {
		printf("read() failed: %m\n");
		abort();
	} else if (!r) {
		printf("unexpected EOF on read()\n");
		abort();
	}

	was_sealed = mfd_assert_get_seals(mfd) & F_SEAL_WRITE;

	/* Wait for sealing-thread to finish and verify that it
	 * successfully sealed the file after the second try. */
	join_sealing_thread(pid);
	mfd_assert_has_seals(mfd, F_SEAL_WRITE);

	/* *IF* the memfd-object was sealed at the time our read() returned,
	 * then the kernel did a page-replacement or canceled the read() (or
	 * whatever magic it did..). In that case, the memfd object is still
	 * all zero.
	 * In case the memfd-object was *not* sealed, the read() was successfull
	 * and the memfd object must *not* be all zero.
	 * Note that in real scenarios, there might be a mixture of both, but
	 * in this test-cases, we have explicit 200ms delays which should be
	 * enough to avoid any in-flight writes. */

	p = mfd_assert_mmap_private(mfd);
	if (was_sealed && memcmp(p, zero, mfd_def_size)) {
		printf("memfd sealed during read() but data not discarded\n");
		abort();
	} else if (!was_sealed && !memcmp(p, zero, mfd_def_size)) {
		printf("memfd sealed after read() but data discarded\n");
		abort();
	}

	close(mfd);
	close(fd);

	printf("fuse: DONE\n");
	free(zero);

	return 0;
}