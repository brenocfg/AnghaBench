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
struct v2r1_disk_dqblk {int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curspace; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; } ;
struct mem_dqblk {void* dqb_itime; void* dqb_btime; void* dqb_curspace; void* dqb_bsoftlimit; void* dqb_bhardlimit; void* dqb_curinodes; void* dqb_isoftlimit; void* dqb_ihardlimit; } ;
struct dquot {struct mem_dqblk dq_dqb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (struct v2r1_disk_dqblk*,void*,int) ; 
 int /*<<< orphan*/  memset (struct v2r1_disk_dqblk*,int /*<<< orphan*/ ,int) ; 
 void* v2_qbtos (void*) ; 

__attribute__((used)) static void v2r1_disk2memdqb(struct dquot *dquot, void *dp)
{
	struct v2r1_disk_dqblk *d = dp, empty;
	struct mem_dqblk *m = &dquot->dq_dqb;

	m->dqb_ihardlimit = le64_to_cpu(d->dqb_ihardlimit);
	m->dqb_isoftlimit = le64_to_cpu(d->dqb_isoftlimit);
	m->dqb_curinodes = le64_to_cpu(d->dqb_curinodes);
	m->dqb_itime = le64_to_cpu(d->dqb_itime);
	m->dqb_bhardlimit = v2_qbtos(le64_to_cpu(d->dqb_bhardlimit));
	m->dqb_bsoftlimit = v2_qbtos(le64_to_cpu(d->dqb_bsoftlimit));
	m->dqb_curspace = le64_to_cpu(d->dqb_curspace);
	m->dqb_btime = le64_to_cpu(d->dqb_btime);
	/* We need to escape back all-zero structure */
	memset(&empty, 0, sizeof(struct v2r1_disk_dqblk));
	empty.dqb_itime = cpu_to_le64(1);
	if (!memcmp(&empty, dp, sizeof(struct v2r1_disk_dqblk)))
		m->dqb_itime = 0;
}