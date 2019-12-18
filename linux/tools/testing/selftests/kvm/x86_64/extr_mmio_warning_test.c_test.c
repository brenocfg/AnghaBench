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
struct thread_context {int kvmcpu; struct kvm_run* run; } ;
struct kvm_run {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_CREATE_VCPU ; 
 int /*<<< orphan*/  KVM_CREATE_VM ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int NTHREAD ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thr ; 
 int /*<<< orphan*/  usleep (int) ; 

void test(void)
{
	int i, kvm, kvmvm, kvmcpu;
	pthread_t th[NTHREAD];
	struct kvm_run *run;
	struct thread_context tc;

	kvm = open("/dev/kvm", O_RDWR);
	TEST_ASSERT(kvm != -1, "failed to open /dev/kvm");
	kvmvm = ioctl(kvm, KVM_CREATE_VM, 0);
	TEST_ASSERT(kvmvm != -1, "KVM_CREATE_VM failed");
	kvmcpu = ioctl(kvmvm, KVM_CREATE_VCPU, 0);
	TEST_ASSERT(kvmcpu != -1, "KVM_CREATE_VCPU failed");
	run = (struct kvm_run *)mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED,
				    kvmcpu, 0);
	tc.kvmcpu = kvmcpu;
	tc.run = run;
	srand(getpid());
	for (i = 0; i < NTHREAD; i++) {
		pthread_create(&th[i], NULL, thr, (void *)(uintptr_t)&tc);
		usleep(rand() % 10000);
	}
	for (i = 0; i < NTHREAD; i++)
		pthread_join(th[i], NULL);
}