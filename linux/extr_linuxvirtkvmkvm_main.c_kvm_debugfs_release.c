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
struct kvm_stat_data {int /*<<< orphan*/  kvm; } ;
struct inode {scalar_t__ i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_put_kvm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_attr_release (struct inode*,struct file*) ; 

__attribute__((used)) static int kvm_debugfs_release(struct inode *inode, struct file *file)
{
	struct kvm_stat_data *stat_data = (struct kvm_stat_data *)
					  inode->i_private;

	simple_attr_release(inode, file);
	kvm_put_kvm(stat_data->kvm);

	return 0;
}