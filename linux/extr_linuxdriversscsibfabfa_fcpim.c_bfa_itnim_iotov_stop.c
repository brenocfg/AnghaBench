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
struct bfa_itnim_s {int /*<<< orphan*/  timer; scalar_t__ iotov_active; } ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 int /*<<< orphan*/  bfa_timer_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_itnim_iotov_stop(struct bfa_itnim_s *itnim)
{
	if (itnim->iotov_active) {
		itnim->iotov_active = BFA_FALSE;
		bfa_timer_stop(&itnim->timer);
	}
}