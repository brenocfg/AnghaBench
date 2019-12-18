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
struct seq_file {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TRANSPARENT_HUGEPAGE ; 
 int IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMF_DISABLE_THP ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void task_thp_status(struct seq_file *m, struct mm_struct *mm)
{
	bool thp_enabled = IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE);

	if (thp_enabled)
		thp_enabled = !test_bit(MMF_DISABLE_THP, &mm->flags);
	seq_printf(m, "THP_enabled:\t%d\n", thp_enabled);
}