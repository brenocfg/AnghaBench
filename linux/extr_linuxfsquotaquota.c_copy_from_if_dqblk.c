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
struct qc_dqblk {int d_fieldmask; int /*<<< orphan*/  d_ino_timer; int /*<<< orphan*/  d_spc_timer; int /*<<< orphan*/  d_ino_count; int /*<<< orphan*/  d_ino_softlimit; int /*<<< orphan*/  d_ino_hardlimit; int /*<<< orphan*/  d_space; void* d_spc_softlimit; void* d_spc_hardlimit; } ;
struct if_dqblk {int dqb_valid; int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; int /*<<< orphan*/  dqb_curspace; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; } ;

/* Variables and functions */
 int QC_INO_COUNT ; 
 int QC_INO_HARD ; 
 int QC_INO_SOFT ; 
 int QC_INO_TIMER ; 
 int QC_SPACE ; 
 int QC_SPC_HARD ; 
 int QC_SPC_SOFT ; 
 int QC_SPC_TIMER ; 
 int QIF_BLIMITS ; 
 int QIF_BTIME ; 
 int QIF_ILIMITS ; 
 int QIF_INODES ; 
 int QIF_ITIME ; 
 int QIF_SPACE ; 
 void* qbtos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_from_if_dqblk(struct qc_dqblk *dst, struct if_dqblk *src)
{
	dst->d_spc_hardlimit = qbtos(src->dqb_bhardlimit);
	dst->d_spc_softlimit = qbtos(src->dqb_bsoftlimit);
	dst->d_space = src->dqb_curspace;
	dst->d_ino_hardlimit = src->dqb_ihardlimit;
	dst->d_ino_softlimit = src->dqb_isoftlimit;
	dst->d_ino_count = src->dqb_curinodes;
	dst->d_spc_timer = src->dqb_btime;
	dst->d_ino_timer = src->dqb_itime;

	dst->d_fieldmask = 0;
	if (src->dqb_valid & QIF_BLIMITS)
		dst->d_fieldmask |= QC_SPC_SOFT | QC_SPC_HARD;
	if (src->dqb_valid & QIF_SPACE)
		dst->d_fieldmask |= QC_SPACE;
	if (src->dqb_valid & QIF_ILIMITS)
		dst->d_fieldmask |= QC_INO_SOFT | QC_INO_HARD;
	if (src->dqb_valid & QIF_INODES)
		dst->d_fieldmask |= QC_INO_COUNT;
	if (src->dqb_valid & QIF_BTIME)
		dst->d_fieldmask |= QC_SPC_TIMER;
	if (src->dqb_valid & QIF_ITIME)
		dst->d_fieldmask |= QC_INO_TIMER;
}