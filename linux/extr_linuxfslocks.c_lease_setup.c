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
struct file_lock {int /*<<< orphan*/  fl_fasync; struct file* fl_file; } ;
struct file {int dummy; } ;
struct fasync_struct {int /*<<< orphan*/  fa_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_TGID ; 
 int /*<<< orphan*/  __f_setown (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  fasync_insert_entry (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ *,struct fasync_struct*) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lease_setup(struct file_lock *fl, void **priv)
{
	struct file *filp = fl->fl_file;
	struct fasync_struct *fa = *priv;

	/*
	 * fasync_insert_entry() returns the old entry if any. If there was no
	 * old entry, then it used "priv" and inserted it into the fasync list.
	 * Clear the pointer to indicate that it shouldn't be freed.
	 */
	if (!fasync_insert_entry(fa->fa_fd, filp, &fl->fl_fasync, fa))
		*priv = NULL;

	__f_setown(filp, task_pid(current), PIDTYPE_TGID, 0);
}