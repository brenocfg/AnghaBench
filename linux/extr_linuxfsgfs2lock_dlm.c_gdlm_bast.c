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
struct gfs2_glock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DLM_LOCK_CW 130 
#define  DLM_LOCK_EX 129 
#define  DLM_LOCK_PR 128 
 int /*<<< orphan*/  LM_ST_DEFERRED ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  LM_ST_UNLOCKED ; 
 int /*<<< orphan*/  gfs2_glock_cb (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void gdlm_bast(void *arg, int mode)
{
	struct gfs2_glock *gl = arg;

	switch (mode) {
	case DLM_LOCK_EX:
		gfs2_glock_cb(gl, LM_ST_UNLOCKED);
		break;
	case DLM_LOCK_CW:
		gfs2_glock_cb(gl, LM_ST_DEFERRED);
		break;
	case DLM_LOCK_PR:
		gfs2_glock_cb(gl, LM_ST_SHARED);
		break;
	default:
		pr_err("unknown bast mode %d\n", mode);
		BUG();
	}
}