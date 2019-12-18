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
struct ext4_sb_info {TYPE_1__* s_journal; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  j_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int task_pid_vnr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t journal_task_show(struct ext4_sb_info *sbi, char *buf)
{
	if (!sbi->s_journal)
		return snprintf(buf, PAGE_SIZE, "<none>\n");
	return snprintf(buf, PAGE_SIZE, "%d\n",
			task_pid_vnr(sbi->s_journal->j_task));
}