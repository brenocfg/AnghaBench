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
struct cpuset {int partition_root_state; } ;

/* Variables and functions */
#define  PRS_DISABLED 130 
#define  PRS_ENABLED 129 
#define  PRS_ERROR 128 
 struct cpuset* css_cs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_css (struct seq_file*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int sched_partition_show(struct seq_file *seq, void *v)
{
	struct cpuset *cs = css_cs(seq_css(seq));

	switch (cs->partition_root_state) {
	case PRS_ENABLED:
		seq_puts(seq, "root\n");
		break;
	case PRS_DISABLED:
		seq_puts(seq, "member\n");
		break;
	case PRS_ERROR:
		seq_puts(seq, "root invalid\n");
		break;
	}
	return 0;
}