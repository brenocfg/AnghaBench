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
struct exp_flavor_info {int flags; int /*<<< orphan*/  pseudoflavor; } ;

/* Variables and functions */
 scalar_t__ secinfo_flags_equal (int,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_secinfo_run(struct seq_file *m, struct exp_flavor_info **fp, struct exp_flavor_info *end)
{
	int flags;

	flags = (*fp)->flags;
	seq_printf(m, ",sec=%d", (*fp)->pseudoflavor);
	(*fp)++;
	while (*fp != end && secinfo_flags_equal(flags, (*fp)->flags)) {
		seq_printf(m, ":%d", (*fp)->pseudoflavor);
		(*fp)++;
	}
	return flags;
}