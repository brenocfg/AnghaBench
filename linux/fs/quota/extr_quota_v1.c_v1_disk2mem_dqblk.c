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
struct v1_disk_dqblk {int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_curblocks; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; } ;
struct mem_dqblk {int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_itime; void* dqb_curspace; void* dqb_bsoftlimit; void* dqb_bhardlimit; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; } ;

/* Variables and functions */
 void* v1_qbtos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v1_disk2mem_dqblk(struct mem_dqblk *m, struct v1_disk_dqblk *d)
{
	m->dqb_ihardlimit = d->dqb_ihardlimit;
	m->dqb_isoftlimit = d->dqb_isoftlimit;
	m->dqb_curinodes = d->dqb_curinodes;
	m->dqb_bhardlimit = v1_qbtos(d->dqb_bhardlimit);
	m->dqb_bsoftlimit = v1_qbtos(d->dqb_bsoftlimit);
	m->dqb_curspace = v1_qbtos(d->dqb_curblocks);
	m->dqb_itime = d->dqb_itime;
	m->dqb_btime = d->dqb_btime;
}