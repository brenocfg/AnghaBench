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
struct file_system_type {int dummy; } ;
struct exofs_mountopt {char const* dev_name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  exofs_fill_super ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 struct dentry* mount_nodev (struct file_system_type*,int,struct exofs_mountopt*,int /*<<< orphan*/ ) ; 
 int parse_options (void*,struct exofs_mountopt*) ; 

__attribute__((used)) static struct dentry *exofs_mount(struct file_system_type *type,
			  int flags, const char *dev_name,
			  void *data)
{
	struct exofs_mountopt opts;
	int ret;

	ret = parse_options(data, &opts);
	if (ret) {
		kfree(opts.dev_name);
		return ERR_PTR(ret);
	}

	if (!opts.dev_name)
		opts.dev_name = dev_name;
	return mount_nodev(type, flags, &opts, exofs_fill_super);
}