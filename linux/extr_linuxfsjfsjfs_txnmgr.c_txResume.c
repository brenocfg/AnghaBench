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
struct jfs_log {int /*<<< orphan*/  syncwait; int /*<<< orphan*/  flag; } ;
struct TYPE_2__ {struct jfs_log* log; } ;

/* Variables and functions */
 TYPE_1__* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  TXN_WAKEUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_QUIESCE ; 

void txResume(struct super_block *sb)
{
	struct jfs_log *log = JFS_SBI(sb)->log;

	clear_bit(log_QUIESCE, &log->flag);
	TXN_WAKEUP(&log->syncwait);
}