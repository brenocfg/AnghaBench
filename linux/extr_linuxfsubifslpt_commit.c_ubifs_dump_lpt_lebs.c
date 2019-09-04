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
struct ubifs_info {int lpt_lebs; scalar_t__ lpt_first; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  dump_lpt_leb (struct ubifs_info const*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

void ubifs_dump_lpt_lebs(const struct ubifs_info *c)
{
	int i;

	pr_err("(pid %d) start dumping all LPT LEBs\n", current->pid);
	for (i = 0; i < c->lpt_lebs; i++)
		dump_lpt_leb(c, i + c->lpt_first);
	pr_err("(pid %d) finish dumping all LPT LEBs\n", current->pid);
}