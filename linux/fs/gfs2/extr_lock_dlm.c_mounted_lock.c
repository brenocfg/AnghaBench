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
typedef  int /*<<< orphan*/  uint32_t ;
struct lm_lockstruct {int /*<<< orphan*/  ls_mounted_lksb; } ;
struct gfs2_sbd {struct lm_lockstruct sd_lockstruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_MOUNTED_LOCK ; 
 int sync_lock (struct gfs2_sbd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mounted_lock(struct gfs2_sbd *sdp, int mode, uint32_t flags)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	return sync_lock(sdp, mode, flags, GFS2_MOUNTED_LOCK,
			 &ls->ls_mounted_lksb, "mounted_lock");
}