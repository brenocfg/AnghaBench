#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct qc_state {int /*<<< orphan*/  s_incoredqs; TYPE_2__* s_state; } ;
struct TYPE_5__ {int ar_quota; } ;
struct gfs2_sbd {TYPE_4__* sd_quota_inode; TYPE_1__ sd_args; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_blocks; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_no_addr; } ;
struct TYPE_6__ {int flags; int nextents; int /*<<< orphan*/  blocks; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 TYPE_3__* GFS2_I (TYPE_4__*) ; 
#define  GFS2_QUOTA_ACCOUNT 130 
#define  GFS2_QUOTA_OFF 129 
#define  GFS2_QUOTA_ON 128 
 size_t GRPQUOTA ; 
 int QCI_ACCT_ENABLED ; 
 int QCI_LIMITS_ENFORCED ; 
 int QCI_SYSFILE ; 
 size_t USRQUOTA ; 
 int /*<<< orphan*/  gfs2_qd_lru ; 
 int /*<<< orphan*/  list_lru_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct qc_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfs2_quota_get_state(struct super_block *sb, struct qc_state *state)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;

	memset(state, 0, sizeof(*state));

	switch (sdp->sd_args.ar_quota) {
	case GFS2_QUOTA_ON:
		state->s_state[USRQUOTA].flags |= QCI_LIMITS_ENFORCED;
		state->s_state[GRPQUOTA].flags |= QCI_LIMITS_ENFORCED;
		/*FALLTHRU*/
	case GFS2_QUOTA_ACCOUNT:
		state->s_state[USRQUOTA].flags |= QCI_ACCT_ENABLED |
						  QCI_SYSFILE;
		state->s_state[GRPQUOTA].flags |= QCI_ACCT_ENABLED |
						  QCI_SYSFILE;
		break;
	case GFS2_QUOTA_OFF:
		break;
	}
	if (sdp->sd_quota_inode) {
		state->s_state[USRQUOTA].ino =
					GFS2_I(sdp->sd_quota_inode)->i_no_addr;
		state->s_state[USRQUOTA].blocks = sdp->sd_quota_inode->i_blocks;
	}
	state->s_state[USRQUOTA].nextents = 1;	/* unsupported */
	state->s_state[GRPQUOTA] = state->s_state[USRQUOTA];
	state->s_incoredqs = list_lru_count(&gfs2_qd_lru);
	return 0;
}