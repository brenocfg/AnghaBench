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
struct kvm_stats_debugfs_item {int mode; size_t kind; scalar_t__ name; int /*<<< orphan*/  offset; } ;
struct kvm_stat_data {int mode; int /*<<< orphan*/  offset; struct kvm* kvm; } ;
struct kvm {int /*<<< orphan*/  debugfs_dentry; struct kvm_stat_data** debugfs_stat_data; } ;
typedef  int /*<<< orphan*/  dir_name ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int ITOA_MAX_LEN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (scalar_t__,int,int /*<<< orphan*/ ,struct kvm_stat_data*,int /*<<< orphan*/ ) ; 
 struct kvm_stats_debugfs_item* debugfs_entries ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 struct kvm_stat_data** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_debugfs_dir ; 
 int /*<<< orphan*/  kvm_debugfs_num_entries ; 
 struct kvm_stat_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/ * stat_fops_per_vm ; 
 int task_pid_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_create_vm_debugfs(struct kvm *kvm, int fd)
{
	char dir_name[ITOA_MAX_LEN * 2];
	struct kvm_stat_data *stat_data;
	struct kvm_stats_debugfs_item *p;

	if (!debugfs_initialized())
		return 0;

	snprintf(dir_name, sizeof(dir_name), "%d-%d", task_pid_nr(current), fd);
	kvm->debugfs_dentry = debugfs_create_dir(dir_name, kvm_debugfs_dir);

	kvm->debugfs_stat_data = kcalloc(kvm_debugfs_num_entries,
					 sizeof(*kvm->debugfs_stat_data),
					 GFP_KERNEL_ACCOUNT);
	if (!kvm->debugfs_stat_data)
		return -ENOMEM;

	for (p = debugfs_entries; p->name; p++) {
		stat_data = kzalloc(sizeof(*stat_data), GFP_KERNEL_ACCOUNT);
		if (!stat_data)
			return -ENOMEM;

		stat_data->kvm = kvm;
		stat_data->offset = p->offset;
		stat_data->mode = p->mode ? p->mode : 0644;
		kvm->debugfs_stat_data[p - debugfs_entries] = stat_data;
		debugfs_create_file(p->name, stat_data->mode, kvm->debugfs_dentry,
				    stat_data, stat_fops_per_vm[p->kind]);
	}
	return 0;
}