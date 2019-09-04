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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  QT_TREEOFF ; 
 int /*<<< orphan*/  find_tree_dqentry (struct qtree_mem_dqinfo*,struct dquot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline loff_t find_dqentry(struct qtree_mem_dqinfo *info,
				  struct dquot *dquot)
{
	return find_tree_dqentry(info, dquot, QT_TREEOFF, 0);
}