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
struct gfs2_trans {unsigned int tr_num_databuf_new; unsigned int tr_num_databuf_rm; int /*<<< orphan*/  tr_databuf; } ;
struct gfs2_sbd {int dummy; } ;

/* Variables and functions */
 unsigned int databuf_limit (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_before_commit (struct gfs2_sbd*,unsigned int,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void databuf_lo_before_commit(struct gfs2_sbd *sdp, struct gfs2_trans *tr)
{
	unsigned int limit = databuf_limit(sdp);
	unsigned int nbuf;
	if (tr == NULL)
		return;
	nbuf = tr->tr_num_databuf_new - tr->tr_num_databuf_rm;
	gfs2_before_commit(sdp, limit, nbuf, &tr->tr_databuf, 1);
}