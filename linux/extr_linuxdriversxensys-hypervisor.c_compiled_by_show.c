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
struct xen_compile_info {char* compile_by; } ;
struct hyp_sysfs_attr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_xen_version (int /*<<< orphan*/ ,struct xen_compile_info*) ; 
 int /*<<< orphan*/  XENVER_compile_info ; 
 int /*<<< orphan*/  kfree (struct xen_compile_info*) ; 
 struct xen_compile_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t compiled_by_show(struct hyp_sysfs_attr *attr, char *buffer)
{
	int ret = -ENOMEM;
	struct xen_compile_info *info;

	info = kmalloc(sizeof(struct xen_compile_info), GFP_KERNEL);
	if (info) {
		ret = HYPERVISOR_xen_version(XENVER_compile_info, info);
		if (!ret)
			ret = sprintf(buffer, "%s\n", info->compile_by);
		kfree(info);
	}

	return ret;
}