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
struct bfa_itnim_s {TYPE_1__* fcpim; int /*<<< orphan*/  timer; int /*<<< orphan*/  bfa; int /*<<< orphan*/  iotov_active; } ;
struct TYPE_2__ {scalar_t__ path_tov; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_itnim_hold_io (struct bfa_itnim_s*) ; 
 int /*<<< orphan*/  bfa_itnim_iotov ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_itnim_s*,scalar_t__) ; 

__attribute__((used)) static void
bfa_itnim_iotov_start(struct bfa_itnim_s *itnim)
{
	if (itnim->fcpim->path_tov > 0) {

		itnim->iotov_active = BFA_TRUE;
		WARN_ON(!bfa_itnim_hold_io(itnim));
		bfa_timer_start(itnim->bfa, &itnim->timer,
			bfa_itnim_iotov, itnim, itnim->fcpim->path_tov);
	}
}