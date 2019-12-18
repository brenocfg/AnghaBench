#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct ceph_inode_info {TYPE_1__ i_snap_btime; } ;

/* Variables and functions */

__attribute__((used)) static bool ceph_vxattrcb_snap_btime_exists(struct ceph_inode_info *ci)
{
	return (ci->i_snap_btime.tv_sec != 0 || ci->i_snap_btime.tv_nsec != 0);
}