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
struct v1_disk_dqblk {int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_itime; void* dqb_curblocks; void* dqb_bsoftlimit; void* dqb_bhardlimit; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; } ;
struct mem_dqblk {int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_curspace; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; } ;

/* Variables and functions */
 void* v1_stoqb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v1_mem2disk_dqblk(struct v1_disk_dqblk *d, struct mem_dqblk *m)
{
	d->dqb_ihardlimit = m->dqb_ihardlimit;
	d->dqb_isoftlimit = m->dqb_isoftlimit;
	d->dqb_curinodes = m->dqb_curinodes;
	d->dqb_bhardlimit = v1_stoqb(m->dqb_bhardlimit);
	d->dqb_bsoftlimit = v1_stoqb(m->dqb_bsoftlimit);
	d->dqb_curblocks = v1_stoqb(m->dqb_curspace);
	d->dqb_itime = m->dqb_itime;
	d->dqb_btime = m->dqb_btime;
}