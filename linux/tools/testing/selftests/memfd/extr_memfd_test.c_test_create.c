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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MFD_ALLOW_SEALING ; 
 int MFD_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 char* memfd_str ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int mfd_assert_new (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfd_fail_new (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void test_create(void)
{
	char buf[2048];
	int fd;

	printf("%s CREATE\n", memfd_str);

	/* test NULL name */
	mfd_fail_new(NULL, 0);

	/* test over-long name (not zero-terminated) */
	memset(buf, 0xff, sizeof(buf));
	mfd_fail_new(buf, 0);

	/* test over-long zero-terminated name */
	memset(buf, 0xff, sizeof(buf));
	buf[sizeof(buf) - 1] = 0;
	mfd_fail_new(buf, 0);

	/* verify "" is a valid name */
	fd = mfd_assert_new("", 0, 0);
	close(fd);

	/* verify invalid O_* open flags */
	mfd_fail_new("", 0x0100);
	mfd_fail_new("", ~MFD_CLOEXEC);
	mfd_fail_new("", ~MFD_ALLOW_SEALING);
	mfd_fail_new("", ~0);
	mfd_fail_new("", 0x80000000U);

	/* verify MFD_CLOEXEC is allowed */
	fd = mfd_assert_new("", 0, MFD_CLOEXEC);
	close(fd);

	/* verify MFD_ALLOW_SEALING is allowed */
	fd = mfd_assert_new("", 0, MFD_ALLOW_SEALING);
	close(fd);

	/* verify MFD_ALLOW_SEALING | MFD_CLOEXEC is allowed */
	fd = mfd_assert_new("", 0, MFD_ALLOW_SEALING | MFD_CLOEXEC);
	close(fd);
}