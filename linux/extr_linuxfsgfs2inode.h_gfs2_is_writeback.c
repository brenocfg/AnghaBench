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
struct TYPE_2__ {scalar_t__ ar_data; } ;
struct gfs2_sbd {TYPE_1__ sd_args; } ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 scalar_t__ GFS2_DATA_WRITEBACK ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_is_jdata (struct gfs2_inode const*) ; 

__attribute__((used)) static inline int gfs2_is_writeback(const struct gfs2_inode *ip)
{
	const struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	return (sdp->sd_args.ar_data == GFS2_DATA_WRITEBACK) && !gfs2_is_jdata(ip);
}