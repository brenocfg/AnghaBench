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
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  qid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int GRPQUOTA ; 
#define  Q_GETFMT 135 
#define  Q_GETINFO 134 
#define  Q_GETQUOTA 133 
#define  Q_SYNC 132 
#define  Q_XGETQSTAT 131 
#define  Q_XGETQSTATV 130 
#define  Q_XGETQUOTA 129 
#define  Q_XQUOTASYNC 128 
 int USRQUOTA ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_euid () ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  in_egroup_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int security_quotactl (int,int,int /*<<< orphan*/ ,struct super_block*) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_quotactl_permission(struct super_block *sb, int type, int cmd,
				     qid_t id)
{
	switch (cmd) {
	/* these commands do not require any special privilegues */
	case Q_GETFMT:
	case Q_SYNC:
	case Q_GETINFO:
	case Q_XGETQSTAT:
	case Q_XGETQSTATV:
	case Q_XQUOTASYNC:
		break;
	/* allow to query information for dquots we "own" */
	case Q_GETQUOTA:
	case Q_XGETQUOTA:
		if ((type == USRQUOTA && uid_eq(current_euid(), make_kuid(current_user_ns(), id))) ||
		    (type == GRPQUOTA && in_egroup_p(make_kgid(current_user_ns(), id))))
			break;
		/*FALLTHROUGH*/
	default:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
	}

	return security_quotactl(cmd, type, id, sb);
}