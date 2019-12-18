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
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; TYPE_2__ sd_lockstruct; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lm_mount; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  SDF_NOJOURNALID ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_on_journal(struct gfs2_sbd *sdp)
{
	if (sdp->sd_lockstruct.ls_ops->lm_mount == NULL)
		return 0;

	return wait_on_bit(&sdp->sd_flags, SDF_NOJOURNALID, TASK_INTERRUPTIBLE)
		? -EINTR : 0;
}