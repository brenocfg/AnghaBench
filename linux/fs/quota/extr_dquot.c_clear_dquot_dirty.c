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
struct dquot {int /*<<< orphan*/  dq_dirty; int /*<<< orphan*/  dq_flags; int /*<<< orphan*/  dq_sb; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int DQUOT_NOLIST_DIRTY ; 
 int /*<<< orphan*/  DQ_MOD_B ; 
 int /*<<< orphan*/  dq_list_lock ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int clear_dquot_dirty(struct dquot *dquot)
{
	if (sb_dqopt(dquot->dq_sb)->flags & DQUOT_NOLIST_DIRTY)
		return test_and_clear_bit(DQ_MOD_B, &dquot->dq_flags);

	spin_lock(&dq_list_lock);
	if (!test_and_clear_bit(DQ_MOD_B, &dquot->dq_flags)) {
		spin_unlock(&dq_list_lock);
		return 0;
	}
	list_del_init(&dquot->dq_dirty);
	spin_unlock(&dq_list_lock);
	return 1;
}