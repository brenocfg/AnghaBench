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
typedef  scalar_t__ u64 ;
typedef  int u16 ;
struct gfs2_inode {scalar_t__ i_no_addr; scalar_t__ i_eattr; } ;

/* Variables and functions */

__attribute__((used)) static u16 gfs2_inode_ra_len(const struct gfs2_inode *ip)
{
	u64 where = ip->i_no_addr + 1;
	if (ip->i_eattr == where)
		return 1;
	return 0;
}