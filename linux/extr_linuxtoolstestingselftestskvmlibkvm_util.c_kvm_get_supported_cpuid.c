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
struct kvm_cpuid2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KSFT_SKIP ; 
 int /*<<< orphan*/  KVM_DEV_PATH ; 
 int /*<<< orphan*/  KVM_GET_SUPPORTED_CPUID ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,int,int /*<<< orphan*/ ) ; 
 struct kvm_cpuid2* allocate_kvm_cpuid2 () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct kvm_cpuid2*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct kvm_cpuid2 *kvm_get_supported_cpuid(void)
{
	static struct kvm_cpuid2 *cpuid;
	int ret;
	int kvm_fd;

	if (cpuid)
		return cpuid;

	cpuid = allocate_kvm_cpuid2();
	kvm_fd = open(KVM_DEV_PATH, O_RDONLY);
	if (kvm_fd < 0)
		exit(KSFT_SKIP);

	ret = ioctl(kvm_fd, KVM_GET_SUPPORTED_CPUID, cpuid);
	TEST_ASSERT(ret == 0, "KVM_GET_SUPPORTED_CPUID failed %d %d\n",
		    ret, errno);

	close(kvm_fd);
	return cpuid;
}