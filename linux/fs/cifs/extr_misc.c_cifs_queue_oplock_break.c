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
struct cifsFileInfo {int /*<<< orphan*/  oplock_break; } ;

/* Variables and functions */
 int /*<<< orphan*/  cifsFileInfo_get (struct cifsFileInfo*) ; 
 int /*<<< orphan*/  cifsoplockd_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cifs_queue_oplock_break(struct cifsFileInfo *cfile)
{
	/*
	 * Bump the handle refcount now while we hold the
	 * open_file_lock to enforce the validity of it for the oplock
	 * break handler. The matching put is done at the end of the
	 * handler.
	 */
	cifsFileInfo_get(cfile);

	queue_work(cifsoplockd_wq, &cfile->oplock_break);
}