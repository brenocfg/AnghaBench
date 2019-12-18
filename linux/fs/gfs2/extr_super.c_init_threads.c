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
struct task_struct {int dummy; } ;
struct gfs2_sbd {struct task_struct* sd_logd_process; struct task_struct* sd_quotad_process; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int) ; 
 int /*<<< orphan*/  gfs2_logd ; 
 int /*<<< orphan*/  gfs2_quotad ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct gfs2_sbd*,char*) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 

__attribute__((used)) static int init_threads(struct gfs2_sbd *sdp)
{
	struct task_struct *p;
	int error = 0;

	p = kthread_run(gfs2_logd, sdp, "gfs2_logd");
	if (IS_ERR(p)) {
		error = PTR_ERR(p);
		fs_err(sdp, "can't start logd thread: %d\n", error);
		return error;
	}
	sdp->sd_logd_process = p;

	p = kthread_run(gfs2_quotad, sdp, "gfs2_quotad");
	if (IS_ERR(p)) {
		error = PTR_ERR(p);
		fs_err(sdp, "can't start quotad thread: %d\n", error);
		goto fail;
	}
	sdp->sd_quotad_process = p;
	return 0;

fail:
	kthread_stop(sdp->sd_logd_process);
	sdp->sd_logd_process = NULL;
	return error;
}