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
typedef  size_t u32 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {TYPE_1__* i_qadata; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_inode; } ;
struct TYPE_2__ {size_t qa_qd_num; int /*<<< orphan*/ ** qa_qd; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIF_QD_LOCKED ; 
 int /*<<< orphan*/  gfs2_assert_warn (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  qdsb_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_quota_unhold(struct gfs2_inode *ip)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	u32 x;

	if (ip->i_qadata == NULL)
		return;
	gfs2_assert_warn(sdp, !test_bit(GIF_QD_LOCKED, &ip->i_flags));

	for (x = 0; x < ip->i_qadata->qa_qd_num; x++) {
		qdsb_put(ip->i_qadata->qa_qd[x]);
		ip->i_qadata->qa_qd[x] = NULL;
	}
	ip->i_qadata->qa_qd_num = 0;
}