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
struct super_block {scalar_t__ dq_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_srcu ; 
 int /*<<< orphan*/  put_dquot_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_dquot_ref (struct super_block*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tofree_head ; 

__attribute__((used)) static void drop_dquot_ref(struct super_block *sb, int type)
{
	LIST_HEAD(tofree_head);

	if (sb->dq_op) {
		remove_dquot_ref(sb, type, &tofree_head);
		synchronize_srcu(&dquot_srcu);
		put_dquot_list(&tofree_head);
	}
}