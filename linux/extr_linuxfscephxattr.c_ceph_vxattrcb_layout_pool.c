#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ceph_osd_client {int /*<<< orphan*/  lock; int /*<<< orphan*/  osdmap; } ;
struct TYPE_5__ {scalar_t__ pool_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_sb; } ;
struct ceph_inode_info {TYPE_2__ i_layout; TYPE_3__ vfs_inode; } ;
struct ceph_fs_client {TYPE_1__* client; } ;
typedef  scalar_t__ s64 ;
struct TYPE_4__ {struct ceph_osd_client osdc; } ;

/* Variables and functions */
 char* ceph_pg_pool_name_by_id (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int snprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t ceph_vxattrcb_layout_pool(struct ceph_inode_info *ci,
					char *val, size_t size)
{
	int ret;
	struct ceph_fs_client *fsc = ceph_sb_to_client(ci->vfs_inode.i_sb);
	struct ceph_osd_client *osdc = &fsc->client->osdc;
	s64 pool = ci->i_layout.pool_id;
	const char *pool_name;

	down_read(&osdc->lock);
	pool_name = ceph_pg_pool_name_by_id(osdc->osdmap, pool);
	if (pool_name)
		ret = snprintf(val, size, "%s", pool_name);
	else
		ret = snprintf(val, size, "%lld", (unsigned long long)pool);
	up_read(&osdc->lock);
	return ret;
}