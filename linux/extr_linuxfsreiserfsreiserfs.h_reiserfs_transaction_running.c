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
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {struct super_block* t_super; } ;
struct TYPE_2__ {struct reiserfs_transaction_handle* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 TYPE_1__* current ; 

__attribute__((used)) static inline int reiserfs_transaction_running(struct super_block *s)
{
	struct reiserfs_transaction_handle *th = current->journal_info;
	if (th && th->t_super == s)
		return 1;
	if (th && th->t_super == NULL)
		BUG();
	return 0;
}