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
typedef  unsigned int u64 ;
struct gfs2_rgrpd {unsigned int rd_reserved; int /*<<< orphan*/  rd_rsspin; } ;
struct gfs2_rbm {struct gfs2_rgrpd* rgd; } ;
struct gfs2_blkreserv {scalar_t__ rs_free; int /*<<< orphan*/  rs_rbm; } ;
struct gfs2_inode {int /*<<< orphan*/  i_sizehint; struct gfs2_blkreserv i_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGRP_RSRV_ADDBLKS ; 
 int /*<<< orphan*/  TRACE_RS_CLAIM ; 
 int /*<<< orphan*/  __rs_deltree (struct gfs2_blkreserv*) ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gfs2_rbm_eq (int /*<<< orphan*/ *,struct gfs2_rbm const*) ; 
 int gfs2_rbm_from_block (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int gfs2_rbm_to_block (struct gfs2_rbm const*) ; 
 scalar_t__ gfs2_rs_active (struct gfs2_blkreserv*) ; 
 unsigned int min (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gfs2_rs (struct gfs2_blkreserv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_adjust_reservation(struct gfs2_inode *ip,
				    const struct gfs2_rbm *rbm, unsigned len)
{
	struct gfs2_blkreserv *rs = &ip->i_res;
	struct gfs2_rgrpd *rgd = rbm->rgd;
	unsigned rlen;
	u64 block;
	int ret;

	spin_lock(&rgd->rd_rsspin);
	if (gfs2_rs_active(rs)) {
		if (gfs2_rbm_eq(&rs->rs_rbm, rbm)) {
			block = gfs2_rbm_to_block(rbm);
			ret = gfs2_rbm_from_block(&rs->rs_rbm, block + len);
			rlen = min(rs->rs_free, len);
			rs->rs_free -= rlen;
			rgd->rd_reserved -= rlen;
			trace_gfs2_rs(rs, TRACE_RS_CLAIM);
			if (rs->rs_free && !ret)
				goto out;
			/* We used up our block reservation, so we should
			   reserve more blocks next time. */
			atomic_add(RGRP_RSRV_ADDBLKS, &ip->i_sizehint);
		}
		__rs_deltree(rs);
	}
out:
	spin_unlock(&rgd->rd_rsspin);
}