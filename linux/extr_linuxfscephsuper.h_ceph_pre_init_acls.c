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
struct inode {int dummy; } ;
struct ceph_acls_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int ceph_pre_init_acls(struct inode *dir, umode_t *mode,
				     struct ceph_acls_info *info)
{
	return 0;
}