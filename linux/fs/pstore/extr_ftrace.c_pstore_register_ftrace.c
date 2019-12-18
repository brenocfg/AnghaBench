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
struct TYPE_2__ {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* psinfo ; 
 int /*<<< orphan*/  pstore_ftrace_dir ; 
 int /*<<< orphan*/  pstore_knob_fops ; 

void pstore_register_ftrace(void)
{
	if (!psinfo->write)
		return;

	pstore_ftrace_dir = debugfs_create_dir("pstore", NULL);

	debugfs_create_file("record_ftrace", 0600, pstore_ftrace_dir, NULL,
			    &pstore_knob_fops);
}