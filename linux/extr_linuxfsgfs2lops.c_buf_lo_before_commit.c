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
struct gfs2_trans {unsigned int tr_num_buf_new; unsigned int tr_num_buf_rm; int /*<<< orphan*/  tr_buf; } ;
struct gfs2_sbd {int dummy; } ;

/* Variables and functions */
 unsigned int buf_limit (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_before_commit (struct gfs2_sbd*,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buf_lo_before_commit(struct gfs2_sbd *sdp, struct gfs2_trans *tr)
{
	unsigned int limit = buf_limit(sdp); /* 503 for 4k blocks */
	unsigned int nbuf;
	if (tr == NULL)
		return;
	nbuf = tr->tr_num_buf_new - tr->tr_num_buf_rm;
	gfs2_before_commit(sdp, limit, nbuf, &tr->tr_buf, 0);
}