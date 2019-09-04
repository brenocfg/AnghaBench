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
struct TYPE_2__ {int /*<<< orphan*/  hotkey; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  enabled (int,int /*<<< orphan*/ ) ; 
 scalar_t__ hotkey_all_mask ; 
 int hotkey_mask_get () ; 
 int /*<<< orphan*/  hotkey_mutex ; 
 int hotkey_status_get (int*) ; 
 int /*<<< orphan*/  hotkey_user_mask ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 TYPE_1__ tp_features ; 

__attribute__((used)) static int hotkey_read(struct seq_file *m)
{
	int res, status;

	if (!tp_features.hotkey) {
		seq_printf(m, "status:\t\tnot supported\n");
		return 0;
	}

	if (mutex_lock_killable(&hotkey_mutex))
		return -ERESTARTSYS;
	res = hotkey_status_get(&status);
	if (!res)
		res = hotkey_mask_get();
	mutex_unlock(&hotkey_mutex);
	if (res)
		return res;

	seq_printf(m, "status:\t\t%s\n", enabled(status, 0));
	if (hotkey_all_mask) {
		seq_printf(m, "mask:\t\t0x%08x\n", hotkey_user_mask);
		seq_printf(m, "commands:\tenable, disable, reset, <mask>\n");
	} else {
		seq_printf(m, "mask:\t\tnot supported\n");
		seq_printf(m, "commands:\tenable, disable, reset\n");
	}

	return 0;
}