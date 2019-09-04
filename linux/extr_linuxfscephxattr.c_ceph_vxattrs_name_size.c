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
struct ceph_vxattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct ceph_vxattr*) ; 
 struct ceph_vxattr* ceph_dir_vxattrs ; 
 size_t ceph_dir_vxattrs_name_size ; 
 struct ceph_vxattr* ceph_file_vxattrs ; 
 size_t ceph_file_vxattrs_name_size ; 

__attribute__((used)) static size_t ceph_vxattrs_name_size(struct ceph_vxattr *vxattrs)
{
	if (vxattrs == ceph_dir_vxattrs)
		return ceph_dir_vxattrs_name_size;
	if (vxattrs == ceph_file_vxattrs)
		return ceph_file_vxattrs_name_size;
	BUG_ON(vxattrs);
	return 0;
}