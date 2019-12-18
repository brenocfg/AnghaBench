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
struct kvm_io_device {int dummy; } ;
struct _ioeventfd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioeventfd_release (struct _ioeventfd*) ; 
 struct _ioeventfd* to_ioeventfd (struct kvm_io_device*) ; 

__attribute__((used)) static void
ioeventfd_destructor(struct kvm_io_device *this)
{
	struct _ioeventfd *p = to_ioeventfd(this);

	ioeventfd_release(p);
}