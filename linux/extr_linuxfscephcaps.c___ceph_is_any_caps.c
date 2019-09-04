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
struct ceph_inode_info {int /*<<< orphan*/  i_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ceph_is_any_caps(struct ceph_inode_info *ci)
{
	return !RB_EMPTY_ROOT(&ci->i_caps);
}