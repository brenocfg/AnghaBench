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
 scalar_t__ rb_first (int /*<<< orphan*/ *) ; 
 scalar_t__ rb_last (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ceph_is_single_caps(struct ceph_inode_info *ci)
{
	return rb_first(&ci->i_caps) == rb_last(&ci->i_caps);
}