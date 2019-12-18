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
 int F_SEAL_GROW ; 
 int F_SEAL_SEAL ; 
 int F_SEAL_SHRINK ; 
 int F_SEAL_WRITE ; 
 int MFD_ALLOW_SEALING ; 
 int MFD_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 char* memfd_str ; 
 int /*<<< orphan*/  mfd_assert_add_seals (int,int) ; 
 int mfd_assert_dup (int) ; 
 int /*<<< orphan*/  mfd_assert_has_seals (int,int) ; 
 int mfd_assert_new (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfd_def_size ; 
 int /*<<< orphan*/  mfd_fail_add_seals (int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 

__attribute__((used)) static void test_share_dup(char *banner, char *b_suffix)
{
	int fd, fd2;

	printf("%s %s %s\n", memfd_str, banner, b_suffix);

	fd = mfd_assert_new("kern_memfd_share_dup",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_assert_has_seals(fd, 0);

	fd2 = mfd_assert_dup(fd);
	mfd_assert_has_seals(fd2, 0);

	mfd_assert_add_seals(fd, F_SEAL_WRITE);
	mfd_assert_has_seals(fd, F_SEAL_WRITE);
	mfd_assert_has_seals(fd2, F_SEAL_WRITE);

	mfd_assert_add_seals(fd2, F_SEAL_SHRINK);
	mfd_assert_has_seals(fd, F_SEAL_WRITE | F_SEAL_SHRINK);
	mfd_assert_has_seals(fd2, F_SEAL_WRITE | F_SEAL_SHRINK);

	mfd_assert_add_seals(fd, F_SEAL_SEAL);
	mfd_assert_has_seals(fd, F_SEAL_WRITE | F_SEAL_SHRINK | F_SEAL_SEAL);
	mfd_assert_has_seals(fd2, F_SEAL_WRITE | F_SEAL_SHRINK | F_SEAL_SEAL);

	mfd_fail_add_seals(fd, F_SEAL_GROW);
	mfd_fail_add_seals(fd2, F_SEAL_GROW);
	mfd_fail_add_seals(fd, F_SEAL_SEAL);
	mfd_fail_add_seals(fd2, F_SEAL_SEAL);

	close(fd2);

	mfd_fail_add_seals(fd, F_SEAL_GROW);
	close(fd);
}