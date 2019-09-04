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
struct ocfs2_dlm_debug {int /*<<< orphan*/ * d_locking_state; int /*<<< orphan*/  d_lockres_tracking; int /*<<< orphan*/  d_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ocfs2_dlm_debug* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 

struct ocfs2_dlm_debug *ocfs2_new_dlm_debug(void)
{
	struct ocfs2_dlm_debug *dlm_debug;

	dlm_debug = kmalloc(sizeof(struct ocfs2_dlm_debug), GFP_KERNEL);
	if (!dlm_debug) {
		mlog_errno(-ENOMEM);
		goto out;
	}

	kref_init(&dlm_debug->d_refcnt);
	INIT_LIST_HEAD(&dlm_debug->d_lockres_tracking);
	dlm_debug->d_locking_state = NULL;
out:
	return dlm_debug;
}