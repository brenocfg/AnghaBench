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
 int MAXQUOTAS ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  dqput_all (struct dquot**) ; 
 struct dquot** i_dquot (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __dquot_drop(struct inode *inode)
{
	int cnt;
	struct dquot **dquots = i_dquot(inode);
	struct dquot *put[MAXQUOTAS];

	spin_lock(&dq_data_lock);
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		put[cnt] = dquots[cnt];
		dquots[cnt] = NULL;
	}
	spin_unlock(&dq_data_lock);
	dqput_all(put);
}