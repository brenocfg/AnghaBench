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
struct inode {int dummy; } ;
struct dquot {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int MAXQUOTAS ; 
 int /*<<< orphan*/  __dquot_drop (struct inode*) ; 
 struct dquot** i_dquot (struct inode*) ; 

void dquot_drop(struct inode *inode)
{
	struct dquot * const *dquots;
	int cnt;

	if (IS_NOQUOTA(inode))
		return;

	/*
	 * Test before calling to rule out calls from proc and such
	 * where we are not allowed to block. Note that this is
	 * actually reliable test even without the lock - the caller
	 * must assure that nobody can come after the DQUOT_DROP and
	 * add quota pointers back anyway.
	 */
	dquots = i_dquot(inode);
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (dquots[cnt])
			break;
	}

	if (cnt < MAXQUOTAS)
		__dquot_drop(inode);
}