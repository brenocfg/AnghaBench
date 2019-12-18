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
 int /*<<< orphan*/  KSFT_SKIP ; 
 int /*<<< orphan*/  KVM_CHECK_EXTENSION ; 
 int /*<<< orphan*/  KVM_DEV_PATH ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ,long) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int kvm_check_cap(long cap)
{
	int ret;
	int kvm_fd;

	kvm_fd = open(KVM_DEV_PATH, O_RDONLY);
	if (kvm_fd < 0)
		exit(KSFT_SKIP);

	ret = ioctl(kvm_fd, KVM_CHECK_EXTENSION, cap);
	TEST_ASSERT(ret != -1, "KVM_CHECK_EXTENSION IOCTL failed,\n"
		"  rc: %i errno: %i", ret, errno);

	close(kvm_fd);

	return ret;
}