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
struct reiserfs_journal {int /*<<< orphan*/ * j_dev_bd; int /*<<< orphan*/  j_dev_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_journal_dev(struct super_block *super,
			       struct reiserfs_journal *journal)
{
	if (journal->j_dev_bd != NULL) {
		blkdev_put(journal->j_dev_bd, journal->j_dev_mode);
		journal->j_dev_bd = NULL;
	}
}