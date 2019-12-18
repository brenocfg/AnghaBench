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
struct seq_file {int dummy; } ;
struct kernfs_root {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CGRP_ROOT_MEMORY_LOCAL_EVENTS ; 
 int CGRP_ROOT_NS_DELEGATE ; 
 TYPE_1__ cgrp_dfl_root ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int cgroup_show_options(struct seq_file *seq, struct kernfs_root *kf_root)
{
	if (cgrp_dfl_root.flags & CGRP_ROOT_NS_DELEGATE)
		seq_puts(seq, ",nsdelegate");
	if (cgrp_dfl_root.flags & CGRP_ROOT_MEMORY_LOCAL_EVENTS)
		seq_puts(seq, ",memory_localevents");
	return 0;
}