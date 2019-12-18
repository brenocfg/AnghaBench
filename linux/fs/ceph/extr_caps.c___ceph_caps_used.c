#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nrpages; } ;
struct TYPE_3__ {TYPE_2__ i_data; int /*<<< orphan*/  i_mode; } ;
struct ceph_inode_info {scalar_t__ i_wrbuffer_ref; scalar_t__ i_wb_ref; scalar_t__ i_wr_ref; TYPE_1__ vfs_inode; scalar_t__ i_rdcache_ref; scalar_t__ i_rd_ref; scalar_t__ i_pin_ref; } ;

/* Variables and functions */
 int CEPH_CAP_FILE_BUFFER ; 
 int CEPH_CAP_FILE_CACHE ; 
 int CEPH_CAP_FILE_RD ; 
 int CEPH_CAP_FILE_WR ; 
 int CEPH_CAP_PIN ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 

int __ceph_caps_used(struct ceph_inode_info *ci)
{
	int used = 0;
	if (ci->i_pin_ref)
		used |= CEPH_CAP_PIN;
	if (ci->i_rd_ref)
		used |= CEPH_CAP_FILE_RD;
	if (ci->i_rdcache_ref ||
	    (!S_ISDIR(ci->vfs_inode.i_mode) && /* ignore readdir cache */
	     ci->vfs_inode.i_data.nrpages))
		used |= CEPH_CAP_FILE_CACHE;
	if (ci->i_wr_ref)
		used |= CEPH_CAP_FILE_WR;
	if (ci->i_wb_ref || ci->i_wrbuffer_ref)
		used |= CEPH_CAP_FILE_BUFFER;
	return used;
}