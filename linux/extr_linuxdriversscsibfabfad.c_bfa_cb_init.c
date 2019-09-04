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
struct bfad_s {int bfad_flags; int /*<<< orphan*/  comp; int /*<<< orphan*/  bfad_tsk; } ;
typedef  scalar_t__ bfa_status_t ;

/* Variables and functions */
 int BFAD_HAL_INIT_DONE ; 
 int BFAD_HAL_INIT_FAIL ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void
bfa_cb_init(void *drv, bfa_status_t init_status)
{
	struct bfad_s	      *bfad = drv;

	if (init_status == BFA_STATUS_OK) {
		bfad->bfad_flags |= BFAD_HAL_INIT_DONE;

		/*
		 * If BFAD_HAL_INIT_FAIL flag is set:
		 * Wake up the kernel thread to start
		 * the bfad operations after HAL init done
		 */
		if ((bfad->bfad_flags & BFAD_HAL_INIT_FAIL)) {
			bfad->bfad_flags &= ~BFAD_HAL_INIT_FAIL;
			wake_up_process(bfad->bfad_tsk);
		}
	}

	complete(&bfad->comp);
}