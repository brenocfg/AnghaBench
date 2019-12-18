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
struct TYPE_2__ {int sb_bsize_shift; } ;
struct gfs2_sbd {int sd_max_height; unsigned int sd_diptrs; TYPE_1__ sd_sb; int /*<<< orphan*/  sd_inptrs; } ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; } ;
typedef  int loff_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_write_calc_reserv (struct gfs2_inode*,int,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void calc_max_reserv(struct gfs2_inode *ip, loff_t *len,
			    unsigned int *data_blocks, unsigned int *ind_blocks,
			    unsigned int max_blocks)
{
	loff_t max = *len;
	const struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	unsigned int tmp, max_data = max_blocks - 3 * (sdp->sd_max_height - 1);

	for (tmp = max_data; tmp > sdp->sd_diptrs;) {
		tmp = DIV_ROUND_UP(tmp, sdp->sd_inptrs);
		max_data -= tmp;
	}

	*data_blocks = max_data;
	*ind_blocks = max_blocks - max_data;
	*len = ((loff_t)max_data - 3) << sdp->sd_sb.sb_bsize_shift;
	if (*len > max) {
		*len = max;
		gfs2_write_calc_reserv(ip, max, data_blocks, ind_blocks);
	}
}