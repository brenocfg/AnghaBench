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
struct kvm_vcpu {int dummy; } ;
struct kvm_io_device {int dummy; } ;
struct _ioeventfd {int /*<<< orphan*/  eventfd; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  eventfd_signal (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ioeventfd_in_range (struct _ioeventfd*,int /*<<< orphan*/ ,int,void const*) ; 
 struct _ioeventfd* to_ioeventfd (struct kvm_io_device*) ; 

__attribute__((used)) static int
ioeventfd_write(struct kvm_vcpu *vcpu, struct kvm_io_device *this, gpa_t addr,
		int len, const void *val)
{
	struct _ioeventfd *p = to_ioeventfd(this);

	if (!ioeventfd_in_range(p, addr, len, val))
		return -EOPNOTSUPP;

	eventfd_signal(p->eventfd, 1);
	return 0;
}