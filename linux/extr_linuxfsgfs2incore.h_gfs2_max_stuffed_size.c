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
struct gfs2_inode {int /*<<< orphan*/  i_inode; } ;
struct gfs2_dinode {int dummy; } ;
struct TYPE_3__ {int sb_bsize; } ;
struct TYPE_4__ {TYPE_1__ sd_sb; } ;

/* Variables and functions */
 TYPE_2__* GFS2_SB (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned gfs2_max_stuffed_size(const struct gfs2_inode *ip)
{
	return GFS2_SB(&ip->i_inode)->sd_sb.sb_bsize - sizeof(struct gfs2_dinode);
}