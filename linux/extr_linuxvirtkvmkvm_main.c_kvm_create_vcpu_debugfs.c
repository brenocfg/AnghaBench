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
struct kvm_vcpu {int vcpu_id; int /*<<< orphan*/  debugfs_dentry; TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  dir_name ;
struct TYPE_2__ {int /*<<< orphan*/  debugfs_dentry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ITOA_MAX_LEN ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int kvm_arch_create_vcpu_debugfs (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_arch_has_vcpu_debugfs () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int kvm_create_vcpu_debugfs(struct kvm_vcpu *vcpu)
{
	char dir_name[ITOA_MAX_LEN * 2];
	int ret;

	if (!kvm_arch_has_vcpu_debugfs())
		return 0;

	if (!debugfs_initialized())
		return 0;

	snprintf(dir_name, sizeof(dir_name), "vcpu%d", vcpu->vcpu_id);
	vcpu->debugfs_dentry = debugfs_create_dir(dir_name,
								vcpu->kvm->debugfs_dentry);
	if (!vcpu->debugfs_dentry)
		return -ENOMEM;

	ret = kvm_arch_create_vcpu_debugfs(vcpu);
	if (ret < 0) {
		debugfs_remove_recursive(vcpu->debugfs_dentry);
		return ret;
	}

	return 0;
}