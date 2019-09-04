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
 int F_SEAL_SHRINK ; 
 int MFD_ALLOW_SEALING ; 
 int MFD_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 char* memfd_str ; 
 int /*<<< orphan*/  mfd_assert_add_seals (int,int) ; 
 int /*<<< orphan*/  mfd_assert_has_seals (int,int) ; 
 int mfd_assert_new (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfd_assert_read (int) ; 
 int /*<<< orphan*/  mfd_assert_write (int) ; 
 int /*<<< orphan*/  mfd_def_size ; 
 int /*<<< orphan*/  mfd_fail_grow (int) ; 
 int /*<<< orphan*/  mfd_fail_grow_write (int) ; 
 int /*<<< orphan*/  mfd_fail_shrink (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void test_seal_resize(void)
{
	int fd;

	printf("%s SEAL-RESIZE\n", memfd_str);

	fd = mfd_assert_new("kern_memfd_seal_resize",
			    mfd_def_size,
			    MFD_CLOEXEC | MFD_ALLOW_SEALING);
	mfd_assert_has_seals(fd, 0);
	mfd_assert_add_seals(fd, F_SEAL_SHRINK | F_SEAL_GROW);
	mfd_assert_has_seals(fd, F_SEAL_SHRINK | F_SEAL_GROW);

	mfd_assert_read(fd);
	mfd_assert_write(fd);
	mfd_fail_shrink(fd);
	mfd_fail_grow(fd);
	mfd_fail_grow_write(fd);

	close(fd);
}