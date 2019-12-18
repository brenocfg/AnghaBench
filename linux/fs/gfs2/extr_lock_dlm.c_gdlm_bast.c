#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ln_sbd; } ;
struct gfs2_glock {TYPE_1__ gl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DLM_LOCK_CW 130 
#define  DLM_LOCK_EX 129 
#define  DLM_LOCK_PR 128 
 int /*<<< orphan*/  LM_ST_DEFERRED ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  LM_ST_UNLOCKED ; 
 int /*<<< orphan*/  fs_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gfs2_glock_cb (struct gfs2_glock*,int /*<<< orphan*/ ) ; 

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
		fs_err(gl->gl_name.ln_sbd, "unknown bast mode %d\n", mode);
		BUG();
	}
}