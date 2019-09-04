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
struct super_block {int dummy; } ;
struct quota_info {int flags; TYPE_1__* info; int /*<<< orphan*/ * files; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqi_fmt_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQUOT_LIMITS_ENABLED ; 
 int DQUOT_QUOTA_SYS_FILE ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOSYS ; 
 unsigned int FS_QUOTA_GDQ_ACCT ; 
 unsigned int FS_QUOTA_PDQ_ACCT ; 
 unsigned int FS_QUOTA_UDQ_ACCT ; 
 int MAXQUOTAS ; 
 int /*<<< orphan*/  dquot_disable (struct super_block*,int,int /*<<< orphan*/ ) ; 
 int dquot_enable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int qtype_enforce_flag (int) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_quota_usage_enabled (struct super_block*,int) ; 

__attribute__((used)) static int dquot_quota_enable(struct super_block *sb, unsigned int flags)
{
	int ret;
	int type;
	struct quota_info *dqopt = sb_dqopt(sb);

	if (!(dqopt->flags & DQUOT_QUOTA_SYS_FILE))
		return -ENOSYS;
	/* Accounting cannot be turned on while fs is mounted */
	flags &= ~(FS_QUOTA_UDQ_ACCT | FS_QUOTA_GDQ_ACCT | FS_QUOTA_PDQ_ACCT);
	if (!flags)
		return -EINVAL;
	for (type = 0; type < MAXQUOTAS; type++) {
		if (!(flags & qtype_enforce_flag(type)))
			continue;
		/* Can't enforce without accounting */
		if (!sb_has_quota_usage_enabled(sb, type))
			return -EINVAL;
		ret = dquot_enable(dqopt->files[type], type,
				   dqopt->info[type].dqi_fmt_id,
				   DQUOT_LIMITS_ENABLED);
		if (ret < 0)
			goto out_err;
	}
	return 0;
out_err:
	/* Backout enforcement enablement we already did */
	for (type--; type >= 0; type--)  {
		if (flags & qtype_enforce_flag(type))
			dquot_disable(sb, type, DQUOT_LIMITS_ENABLED);
	}
	/* Error code translation for better compatibility with XFS */
	if (ret == -EBUSY)
		ret = -EEXIST;
	return ret;
}