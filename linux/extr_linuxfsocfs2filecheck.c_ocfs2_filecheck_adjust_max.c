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
struct ocfs2_filecheck_sysfs_entry {TYPE_1__* fs_fcheck; } ;
struct TYPE_2__ {unsigned int fc_size; unsigned int fc_done; unsigned int fc_max; int /*<<< orphan*/  fc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 unsigned int OCFS2_FILECHECK_MAXSIZE ; 
 unsigned int OCFS2_FILECHECK_MINSIZE ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_filecheck_erase_entries (struct ocfs2_filecheck_sysfs_entry*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ocfs2_filecheck_adjust_max(struct ocfs2_filecheck_sysfs_entry *ent,
			   unsigned int len)
{
	int ret;

	if ((len < OCFS2_FILECHECK_MINSIZE) || (len > OCFS2_FILECHECK_MAXSIZE))
		return -EINVAL;

	spin_lock(&ent->fs_fcheck->fc_lock);
	if (len < (ent->fs_fcheck->fc_size - ent->fs_fcheck->fc_done)) {
		mlog(ML_NOTICE,
		"Cannot set online file check maximum entry number "
		"to %u due to too many pending entries(%u)\n",
		len, ent->fs_fcheck->fc_size - ent->fs_fcheck->fc_done);
		ret = -EBUSY;
	} else {
		if (len < ent->fs_fcheck->fc_size)
			BUG_ON(!ocfs2_filecheck_erase_entries(ent,
				ent->fs_fcheck->fc_size - len));

		ent->fs_fcheck->fc_max = len;
		ret = 0;
	}
	spin_unlock(&ent->fs_fcheck->fc_lock);

	return ret;
}