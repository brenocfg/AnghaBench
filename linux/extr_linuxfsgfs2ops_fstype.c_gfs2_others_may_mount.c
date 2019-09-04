#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ls_ops; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_kobj; TYPE_2__ sd_lockstruct; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* lm_first_done ) (struct gfs2_sbd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  fs_info (struct gfs2_sbd*,char*) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  stub1 (struct gfs2_sbd*) ; 

__attribute__((used)) static void gfs2_others_may_mount(struct gfs2_sbd *sdp)
{
	char *message = "FIRSTMOUNT=Done";
	char *envp[] = { message, NULL };

	fs_info(sdp, "first mount done, others may mount\n");

	if (sdp->sd_lockstruct.ls_ops->lm_first_done)
		sdp->sd_lockstruct.ls_ops->lm_first_done(sdp);

	kobject_uevent_env(&sdp->sd_kobj, KOBJ_CHANGE, envp);
}