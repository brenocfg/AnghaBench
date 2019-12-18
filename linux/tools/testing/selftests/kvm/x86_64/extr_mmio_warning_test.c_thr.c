#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_context {int kvmcpu; struct kvm_run* run; } ;
struct TYPE_2__ {int suberror; } ;
struct kvm_run {int exit_reason; TYPE_1__ internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_RUN ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

void *thr(void *arg)
{
	struct thread_context *tc = (struct thread_context *)arg;
	int res;
	int kvmcpu = tc->kvmcpu;
	struct kvm_run *run = tc->run;

	res = ioctl(kvmcpu, KVM_RUN, 0);
	printf("ret1=%d exit_reason=%d suberror=%d\n",
		res, run->exit_reason, run->internal.suberror);

	return 0;
}