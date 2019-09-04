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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dquot {int dummy; } ;

/* Variables and functions */
 int MAXQUOTAS ; 
 int /*<<< orphan*/  dquot_active (struct inode*) ; 
 struct dquot** i_dquot (struct inode*) ; 
 scalar_t__ sb_has_quota_active (int /*<<< orphan*/ ,int) ; 

bool dquot_initialize_needed(struct inode *inode)
{
	struct dquot **dquots;
	int i;

	if (!dquot_active(inode))
		return false;

	dquots = i_dquot(inode);
	for (i = 0; i < MAXQUOTAS; i++)
		if (!dquots[i] && sb_has_quota_active(inode->i_sb, i))
			return true;
	return false;
}