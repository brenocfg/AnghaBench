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
struct gfs2_trans {int /*<<< orphan*/  tr_num_revoke; int /*<<< orphan*/  tr_flags; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_bufdata {int /*<<< orphan*/  bd_list; } ;
struct TYPE_2__ {struct gfs2_trans* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  TR_TOUCHED ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gfs2_add_revoke (struct gfs2_sbd*,struct gfs2_bufdata*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_trans_add_revoke(struct gfs2_sbd *sdp, struct gfs2_bufdata *bd)
{
	struct gfs2_trans *tr = current->journal_info;

	BUG_ON(!list_empty(&bd->bd_list));
	gfs2_add_revoke(sdp, bd);
	set_bit(TR_TOUCHED, &tr->tr_flags);
	tr->tr_num_revoke++;
}