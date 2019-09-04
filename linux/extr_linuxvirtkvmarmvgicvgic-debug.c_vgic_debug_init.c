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
struct kvm {int /*<<< orphan*/  debugfs_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_debug_fops ; 

void vgic_debug_init(struct kvm *kvm)
{
	debugfs_create_file("vgic-state", 0444, kvm->debugfs_dentry, kvm,
			    &vgic_debug_fops);
}