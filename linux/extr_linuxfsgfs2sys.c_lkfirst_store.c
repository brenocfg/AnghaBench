#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int ls_first; TYPE_2__* ls_ops; } ;
struct TYPE_4__ {scalar_t__ ar_spectator; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_jindex_spin; TYPE_3__ sd_lockstruct; TYPE_1__ sd_args; int /*<<< orphan*/  sd_flags; int /*<<< orphan*/  sd_locking_init; } ;
typedef  int ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/ * lm_mount; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SDF_NOJOURNALID ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_for_completion_killable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t lkfirst_store(struct gfs2_sbd *sdp, const char *buf, size_t len)
{
	unsigned first;
	int rv;

	rv = sscanf(buf, "%u", &first);
	if (rv != 1 || first > 1)
		return -EINVAL;
	rv = wait_for_completion_killable(&sdp->sd_locking_init);
	if (rv)
		return rv;
	spin_lock(&sdp->sd_jindex_spin);
	rv = -EBUSY;
	if (test_bit(SDF_NOJOURNALID, &sdp->sd_flags) == 0)
		goto out;
	rv = -EINVAL;
	if (sdp->sd_args.ar_spectator)
		goto out;
	if (sdp->sd_lockstruct.ls_ops->lm_mount == NULL)
		goto out;
	sdp->sd_lockstruct.ls_first = first;
	rv = 0;
out:
        spin_unlock(&sdp->sd_jindex_spin);
        return rv ? rv : len;
}