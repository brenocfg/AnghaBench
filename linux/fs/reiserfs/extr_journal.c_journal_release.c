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
struct reiserfs_transaction_handle {int dummy; } ;

/* Variables and functions */
 int do_journal_release (struct reiserfs_transaction_handle*,struct super_block*,int /*<<< orphan*/ ) ; 

int journal_release(struct reiserfs_transaction_handle *th,
		    struct super_block *sb)
{
	return do_journal_release(th, sb, 0);
}