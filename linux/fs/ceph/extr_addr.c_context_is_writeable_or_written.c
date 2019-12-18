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
struct inode {int dummy; } ;
struct ceph_snap_context {scalar_t__ seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_put_snap_context (struct ceph_snap_context*) ; 
 struct ceph_snap_context* get_oldest_context (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int context_is_writeable_or_written(struct inode *inode,
					   struct ceph_snap_context *snapc)
{
	struct ceph_snap_context *oldest = get_oldest_context(inode, NULL, NULL);
	int ret = !oldest || snapc->seq <= oldest->seq;

	ceph_put_snap_context(oldest);
	return ret;
}