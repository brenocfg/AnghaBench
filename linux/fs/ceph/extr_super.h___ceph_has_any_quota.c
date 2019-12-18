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
struct ceph_inode_info {scalar_t__ i_max_bytes; scalar_t__ i_max_files; } ;

/* Variables and functions */

__attribute__((used)) static inline bool __ceph_has_any_quota(struct ceph_inode_info *ci)
{
	return ci->i_max_files || ci->i_max_bytes;
}