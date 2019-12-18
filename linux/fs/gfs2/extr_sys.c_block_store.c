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
struct lm_lockstruct {int /*<<< orphan*/  ls_recover_flags; } ;
struct gfs2_sbd {struct lm_lockstruct sd_lockstruct; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_BLOCK_LOCKS ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_glock_thaw (struct gfs2_sbd*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static ssize_t block_store(struct gfs2_sbd *sdp, const char *buf, size_t len)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	int ret, val;

	ret = kstrtoint(buf, 0, &val);
	if (ret)
		return ret;

	if (val == 1)
		set_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);
	else if (val == 0) {
		clear_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags);
		smp_mb__after_atomic();
		gfs2_glock_thaw(sdp);
	} else {
		return -EINVAL;
	}
	return len;
}