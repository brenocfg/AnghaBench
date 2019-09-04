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
struct pids_cgroup {int /*<<< orphan*/  events_limit; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 struct pids_cgroup* css_pids (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_css (struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pids_events_show(struct seq_file *sf, void *v)
{
	struct pids_cgroup *pids = css_pids(seq_css(sf));

	seq_printf(sf, "max %lld\n", (s64)atomic64_read(&pids->events_limit));
	return 0;
}