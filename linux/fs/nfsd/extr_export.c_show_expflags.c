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
struct flags {int flag; scalar_t__** name; } ;

/* Variables and functions */
 struct flags* expflags ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,scalar_t__*) ; 

__attribute__((used)) static void show_expflags(struct seq_file *m, int flags, int mask)
{
	struct flags *flg;
	int state, first = 0;

	for (flg = expflags; flg->flag; flg++) {
		if (flg->flag & ~mask)
			continue;
		state = (flg->flag & flags) ? 0 : 1;
		if (*flg->name[state])
			seq_printf(m, "%s%s", first++?",":"", flg->name[state]);
	}
}