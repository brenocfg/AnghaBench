#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_qcop; } ;
struct TYPE_9__ {int /*<<< orphan*/  qfs_nextents; int /*<<< orphan*/  qfs_nblks; scalar_t__ qfs_ino; } ;
struct TYPE_8__ {int /*<<< orphan*/  qfs_nextents; int /*<<< orphan*/  qfs_nblks; scalar_t__ qfs_ino; } ;
struct TYPE_7__ {int /*<<< orphan*/  qfs_nextents; int /*<<< orphan*/  qfs_nblks; scalar_t__ qfs_ino; } ;
struct qc_state {TYPE_5__* s_state; TYPE_4__ qs_pquota; TYPE_3__ qs_gquota; TYPE_2__ qs_uquota; int /*<<< orphan*/  qs_iwarnlimit; int /*<<< orphan*/  qs_bwarnlimit; int /*<<< orphan*/  qs_rtbtimelimit; int /*<<< orphan*/  qs_itimelimit; int /*<<< orphan*/  qs_btimelimit; int /*<<< orphan*/  s_incoredqs; int /*<<< orphan*/  qs_incoredqs; int /*<<< orphan*/  qs_flags; int /*<<< orphan*/  qs_version; } ;
struct fs_quota_statv {TYPE_5__* s_state; TYPE_4__ qs_pquota; TYPE_3__ qs_gquota; TYPE_2__ qs_uquota; int /*<<< orphan*/  qs_iwarnlimit; int /*<<< orphan*/  qs_bwarnlimit; int /*<<< orphan*/  qs_rtbtimelimit; int /*<<< orphan*/  qs_itimelimit; int /*<<< orphan*/  qs_btimelimit; int /*<<< orphan*/  s_incoredqs; int /*<<< orphan*/  qs_incoredqs; int /*<<< orphan*/  qs_flags; int /*<<< orphan*/  qs_version; } ;
struct TYPE_10__ {int /*<<< orphan*/  nextents; int /*<<< orphan*/  blocks; scalar_t__ ino; int /*<<< orphan*/  ino_warnlimit; int /*<<< orphan*/  spc_warnlimit; int /*<<< orphan*/  rt_spc_timelimit; int /*<<< orphan*/  ino_timelimit; int /*<<< orphan*/  spc_timelimit; } ;
struct TYPE_6__ {int (* get_state ) (struct super_block*,struct qc_state*) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  FS_QSTAT_VERSION ; 
 size_t GRPQUOTA ; 
 size_t PRJQUOTA ; 
 size_t USRQUOTA ; 
 int /*<<< orphan*/  memset (struct qc_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quota_state_to_flags (struct qc_state*) ; 
 int stub1 (struct super_block*,struct qc_state*) ; 

__attribute__((used)) static int quota_getstatev(struct super_block *sb, int type,
			   struct fs_quota_statv *fqs)
{
	struct qc_state state;
	int ret;

	memset(&state, 0, sizeof (struct qc_state));
	ret = sb->s_qcop->get_state(sb, &state);
	if (ret < 0)
		return ret;

	memset(fqs, 0, sizeof(*fqs));
	fqs->qs_version = FS_QSTAT_VERSION;
	fqs->qs_flags = quota_state_to_flags(&state);
	/* No quota enabled? */
	if (!fqs->qs_flags)
		return -ENOSYS;
	fqs->qs_incoredqs = state.s_incoredqs;

	fqs->qs_btimelimit = state.s_state[type].spc_timelimit;
	fqs->qs_itimelimit = state.s_state[type].ino_timelimit;
	fqs->qs_rtbtimelimit = state.s_state[type].rt_spc_timelimit;
	fqs->qs_bwarnlimit = state.s_state[type].spc_warnlimit;
	fqs->qs_iwarnlimit = state.s_state[type].ino_warnlimit;

	/* Inodes may be allocated even if inactive; copy out if present */
	if (state.s_state[USRQUOTA].ino) {
		fqs->qs_uquota.qfs_ino = state.s_state[USRQUOTA].ino;
		fqs->qs_uquota.qfs_nblks = state.s_state[USRQUOTA].blocks;
		fqs->qs_uquota.qfs_nextents = state.s_state[USRQUOTA].nextents;
	}
	if (state.s_state[GRPQUOTA].ino) {
		fqs->qs_gquota.qfs_ino = state.s_state[GRPQUOTA].ino;
		fqs->qs_gquota.qfs_nblks = state.s_state[GRPQUOTA].blocks;
		fqs->qs_gquota.qfs_nextents = state.s_state[GRPQUOTA].nextents;
	}
	if (state.s_state[PRJQUOTA].ino) {
		fqs->qs_pquota.qfs_ino = state.s_state[PRJQUOTA].ino;
		fqs->qs_pquota.qfs_nblks = state.s_state[PRJQUOTA].blocks;
		fqs->qs_pquota.qfs_nextents = state.s_state[PRJQUOTA].nextents;
	}
	return 0;
}