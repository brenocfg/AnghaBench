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
struct kvm_device {struct kvm* kvm; } ;
struct kvm {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct kvm_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_put_kvm (struct kvm*) ; 

__attribute__((used)) static int kvm_device_release(struct inode *inode, struct file *filp)
{
	struct kvm_device *dev = filp->private_data;
	struct kvm *kvm = dev->kvm;

	kvm_put_kvm(kvm);
	return 0;
}