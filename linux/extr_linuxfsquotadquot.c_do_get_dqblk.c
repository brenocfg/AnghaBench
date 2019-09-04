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
struct qc_dqblk {int /*<<< orphan*/  d_ino_timer; int /*<<< orphan*/  d_spc_timer; int /*<<< orphan*/  d_ino_count; scalar_t__ d_space; int /*<<< orphan*/  d_ino_softlimit; int /*<<< orphan*/  d_ino_hardlimit; int /*<<< orphan*/  d_spc_softlimit; int /*<<< orphan*/  d_spc_hardlimit; } ;
struct mem_dqblk {int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; scalar_t__ dqb_rsvspace; scalar_t__ dqb_curspace; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; } ;
struct dquot {int /*<<< orphan*/  dq_dqb_lock; struct mem_dqblk dq_dqb; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct qc_dqblk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_get_dqblk(struct dquot *dquot, struct qc_dqblk *di)
{
	struct mem_dqblk *dm = &dquot->dq_dqb;

	memset(di, 0, sizeof(*di));
	spin_lock(&dquot->dq_dqb_lock);
	di->d_spc_hardlimit = dm->dqb_bhardlimit;
	di->d_spc_softlimit = dm->dqb_bsoftlimit;
	di->d_ino_hardlimit = dm->dqb_ihardlimit;
	di->d_ino_softlimit = dm->dqb_isoftlimit;
	di->d_space = dm->dqb_curspace + dm->dqb_rsvspace;
	di->d_ino_count = dm->dqb_curinodes;
	di->d_spc_timer = dm->dqb_btime;
	di->d_ino_timer = dm->dqb_itime;
	spin_unlock(&dquot->dq_dqb_lock);
}