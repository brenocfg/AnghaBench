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
struct qc_dqblk {int /*<<< orphan*/  d_ino_timer; int /*<<< orphan*/  d_spc_timer; int /*<<< orphan*/  d_ino_count; int /*<<< orphan*/  d_ino_softlimit; int /*<<< orphan*/  d_ino_hardlimit; int /*<<< orphan*/  d_space; int /*<<< orphan*/  d_spc_softlimit; int /*<<< orphan*/  d_spc_hardlimit; } ;
struct if_dqblk {int /*<<< orphan*/  dqb_valid; int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; int /*<<< orphan*/  dqb_curspace; void* dqb_bsoftlimit; void* dqb_bhardlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIF_ALL ; 
 int /*<<< orphan*/  memset (struct if_dqblk*,int /*<<< orphan*/ ,int) ; 
 void* stoqb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_to_if_dqblk(struct if_dqblk *dst, struct qc_dqblk *src)
{
	memset(dst, 0, sizeof(*dst));
	dst->dqb_bhardlimit = stoqb(src->d_spc_hardlimit);
	dst->dqb_bsoftlimit = stoqb(src->d_spc_softlimit);
	dst->dqb_curspace = src->d_space;
	dst->dqb_ihardlimit = src->d_ino_hardlimit;
	dst->dqb_isoftlimit = src->d_ino_softlimit;
	dst->dqb_curinodes = src->d_ino_count;
	dst->dqb_btime = src->d_spc_timer;
	dst->dqb_itime = src->d_ino_timer;
	dst->dqb_valid = QIF_ALL;
}