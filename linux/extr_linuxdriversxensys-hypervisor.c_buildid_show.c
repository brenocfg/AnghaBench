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
struct xen_build_id {int len; char* buf; } ;
struct hyp_sysfs_attr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_xen_version (int /*<<< orphan*/ ,struct xen_build_id*) ; 
 int /*<<< orphan*/  XENVER_build_id ; 
 int /*<<< orphan*/  kfree (struct xen_build_id*) ; 
 struct xen_build_id* kmalloc (int,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t buildid_show(struct hyp_sysfs_attr *attr, char *buffer)
{
	ssize_t ret;
	struct xen_build_id *buildid;

	ret = HYPERVISOR_xen_version(XENVER_build_id, NULL);
	if (ret < 0) {
		if (ret == -EPERM)
			ret = sprintf(buffer, "<denied>");
		return ret;
	}

	buildid = kmalloc(sizeof(*buildid) + ret, GFP_KERNEL);
	if (!buildid)
		return -ENOMEM;

	buildid->len = ret;
	ret = HYPERVISOR_xen_version(XENVER_build_id, buildid);
	if (ret > 0)
		ret = sprintf(buffer, "%s", buildid->buf);
	kfree(buildid);

	return ret;
}