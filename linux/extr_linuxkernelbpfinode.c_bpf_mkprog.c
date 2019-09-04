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
typedef  int /*<<< orphan*/  umode_t ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int bpf_mkobj_ops (struct dentry*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_prog_iops ; 
 int /*<<< orphan*/  bpffs_obj_fops ; 

__attribute__((used)) static int bpf_mkprog(struct dentry *dentry, umode_t mode, void *arg)
{
	return bpf_mkobj_ops(dentry, mode, arg, &bpf_prog_iops,
			     &bpffs_obj_fops);
}