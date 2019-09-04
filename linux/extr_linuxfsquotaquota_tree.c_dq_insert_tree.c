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
struct qtree_mem_dqinfo {int dummy; } ;
struct dquot {int dummy; } ;

/* Variables and functions */
 int QT_TREEOFF ; 
 int do_insert_tree (struct qtree_mem_dqinfo*,struct dquot*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dq_insert_tree(struct qtree_mem_dqinfo *info,
				 struct dquot *dquot)
{
	int tmp = QT_TREEOFF;

#ifdef __QUOTA_QT_PARANOIA
	if (info->dqi_blocks <= QT_TREEOFF) {
		quota_error(dquot->dq_sb, "Quota tree root isn't allocated!");
		return -EIO;
	}
#endif
	return do_insert_tree(info, dquot, &tmp, 0);
}