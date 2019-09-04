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
struct ceph_acls_info {scalar_t__ pagelist; int /*<<< orphan*/  default_acl; int /*<<< orphan*/  acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_pagelist_release (scalar_t__) ; 
 int /*<<< orphan*/  posix_acl_release (int /*<<< orphan*/ ) ; 

void ceph_release_acls_info(struct ceph_acls_info *info)
{
	posix_acl_release(info->acl);
	posix_acl_release(info->default_acl);
	if (info->pagelist)
		ceph_pagelist_release(info->pagelist);
}