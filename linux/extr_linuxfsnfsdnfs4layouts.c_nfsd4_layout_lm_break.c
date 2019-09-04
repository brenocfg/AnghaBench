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
struct file_lock {int /*<<< orphan*/  fl_owner; scalar_t__ fl_break_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_recall_file_layout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nfsd4_layout_lm_break(struct file_lock *fl)
{
	/*
	 * We don't want the locks code to timeout the lease for us;
	 * we'll remove it ourself if a layout isn't returned
	 * in time:
	 */
	fl->fl_break_time = 0;
	nfsd4_recall_file_layout(fl->fl_owner);
	return false;
}