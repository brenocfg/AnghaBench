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
struct seq_file {struct ci_hdrc* private; } ;
struct ci_hdrc {scalar_t__ role; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ CI_ROLE_END ; 
 TYPE_1__* ci_role (struct ci_hdrc*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_role_show(struct seq_file *s, void *data)
{
	struct ci_hdrc *ci = s->private;

	if (ci->role != CI_ROLE_END)
		seq_printf(s, "%s\n", ci_role(ci)->name);

	return 0;
}