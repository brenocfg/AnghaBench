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
 int /*<<< orphan*/  F_SEAL_FUTURE_WRITE ; 
 int MFD_ALLOW_SEALING ; 
 int MFD_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 char* memfd_str ; 
 int /*<<< orphan*/  mfd_assert_add_seals (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_assert_has_seals (int,int /*<<< orphan*/ ) ; 
 void* mfd_assert_mmap_shared (int) ; 
 int mfd_assert_new (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfd_assert_read (int) ; 
 int /*<<< orphan*/  mfd_assert_read_shared (int) ; 
 int mfd_assert_reopen_fd (int) ; 
 int /*<<< orphan*/  mfd_def_size ; 
 int /*<<< orphan*/  mfd_fail_write (int) ; 
 int /*<<< orphan*/  munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void test_seal_future_write(void)
{
	int fd, fd2;
	void *p;

	printf("%s SEAL-FUTURE-WRITE\n", memfd_str);

	fd = mfd_assert_new("kern_memfd_seal_future_write",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);

	p = mfd_assert_mmap_shared(fd);

	mfd_assert_has_seals(fd, 0);

	mfd_assert_add_seals(fd, F_SEAL_FUTURE_WRITE);
	mfd_assert_has_seals(fd, F_SEAL_FUTURE_WRITE);

	/* read should pass, writes should fail */
	mfd_assert_read(fd);
	mfd_assert_read_shared(fd);
	mfd_fail_write(fd);

	fd2 = mfd_assert_reopen_fd(fd);
	/* read should pass, writes should still fail */
	mfd_assert_read(fd2);
	mfd_assert_read_shared(fd2);
	mfd_fail_write(fd2);

	munmap(p, mfd_def_size);
	close(fd2);
	close(fd);
}